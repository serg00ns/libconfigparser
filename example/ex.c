#include <stdio.h>
#include "../configparser.h"

int main() {
    config_t* config = create_config();
    read_config_file(config, "config.cf");

    pair_t *pair;
    while(pair = next_pair(config))
    {
        printf("Key: %s, Value: %s\n", pair->key, pair->value);
    }

    free_config(config);
    return 0;
}
