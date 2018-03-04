#include <iostream>
#include <zconf.h>
#include "mqtt_comm.h"
#include "log.h"
#include "func_in_thread.h"
#include "initial_parameter.h"

using namespace std;

//#include <vector>
//#include <chrono>
//#include "ThreadPool.h"


int main(int argc, char ** argv)
{
    elog_init_config();
    log_i("The FSU Emulator is staring");

    get_config(CONFIG_PATH);

    int process_id = 0;
    int para2 = 0;
    if (argc != 3) {
        log_e("have not input process id(a number).");
        log_e("have not input the second para(0:sent once.1:sent lasting).");
        log_e("the process will continue run with default id value 0.");
        sleep(5);
        goto non_par;
    }

    process_id = atoi(argv[1]);//传入参数保证各进程里的mqtt客户端id不重复
    para2 = atoi(argv[2]);
    if (para2 != 1)
        para2 = 0;

    non_par:
    for (int j = 0; j < THREAD_NUM; ++j) {
        if (!mqtt_init(j, process_id)) {
            mqtt_connect(j);
        }
    }

    sleep(10);

    if (para2 == 0) {
        for (int k = 0; k < THREAD_NUM; ++k) {
            pthread_t tid1;
            pthread_create(&tid1, nullptr, pub_payload1, (void *) k);
        }
    } else {
        for (int  i = 0;  i < THREAD_NUM; ++ i) {//每个子线程都创建一个mqtt客户端
            pthread_t tid;
            pthread_create(&tid, nullptr, pub_payload, (void *) i);
        }
    }

    while(1) {
        sleep(10);
    }
}







//    ThreadPool pool(4);
//    std::vector< std::future<int> > results;

//    for(int i = 0; i < 8; ++i) {
//        results.emplace_back(
//                pool.enqueue([i] {
//                    std::cout << "hello " << i << std::endl;
//                    std::this_thread::sleep_for(std::chrono::seconds(1));
//                    std::cout << "world " << i << std::endl;
//                    return i*i;
//                })
//        );
//    }
//
//    for(auto && result: results)
//        std::cout << result.get() << ' ';
//    std::cout << std::endl;