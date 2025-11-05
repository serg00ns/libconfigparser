# libconfigparser

Header only library for parsing configuration files.

## Usage

### Basic Example

```c
#include "configparser.h"

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
```

### Configuration File Format

```
key = value
another_key = another_value
```

See `example/` directory.