#include <stdio.h>
#include <stdlib.h>

#include "xbc.h"

void log_handler(const log_cb_t* log_data) {
    printf("SDK: %s\n", log_data->log);
}

int rsx_init(int argc, char const *argv[]){
    node_log_cb(log_handler);
    return rsunxer(argc, argv);
}

int main(int argc, char const *argv[]) {
    rsx_init(argc, argv);
    return 0;
}