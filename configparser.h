#ifndef _CONFIGPARSER_H
# define _CONFIGPARSER_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define INITIAL_CAPACITY 256

typedef struct config_s config_t;
typedef struct pair_s pair_t;


struct pair_s {
    char* key;
    char* value;
};

struct config_s {
    pair_t* pairs;
    int size;
    int capacity;
};

config_t* create_config()
{
    config_t* config = (config_t*)malloc(sizeof(config_t));
    config->pairs = (pair_t*)malloc(sizeof(pair_t) * INITIAL_CAPACITY);
    config->size = 0;
    config->capacity = INITIAL_CAPACITY;
    return config;
}

void free_config(config_t* config)
{
    for (int i = 0; i < config->size; i++) {
        free(config->pairs[i].key);
        free(config->pairs[i].value);
    }
    free(config->pairs);
    free(config);
}

int add_pair(config_t* config, const char* key, const char* value)
{
    if (config->size >= config->capacity) {
        config->capacity *= 2;
        config->pairs = (pair_t*)realloc(config->pairs, sizeof(pair_t) * config->capacity);
    }
    config->pairs[config->size].key = strdup(key);
    config->pairs[config->size].value = strdup(value);
    config->size++;
    return 0;
}

const char* get_value(config_t* config, const char* key)
{
    for (int i = 0; i < config->size; i++) {
        if (strcmp(config->pairs[i].key, key) == 0) {
            return config->pairs[i].value;
        }
    }
    return NULL;
}

void read_config_file(config_t* config, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char* equals = strchr(line, '=');
        if (equals) {
            *equals = '\0';
            char* key = line;
            char* value = equals + 1;

            char* newline = strchr(value, '\n');
            if (newline) *newline = '\0';
            add_pair(config, key, value);
        }
    }
    fclose(file);
}

pair_t *next_pair(config_t *config)
{
    static int index = 0;
    pair_t *pair = NULL;

    if (index < config->size) {
        pair = &config->pairs[index];
        index++;
        return pair;
    } else {
        index = 0;
        return NULL;
    }
    return NULL;
}

#endif // _CONFIGPARSER_H+