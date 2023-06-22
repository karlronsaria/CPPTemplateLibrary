# issue

- [x] 2023_06_22_003300
  - system
    - using Visual Studio
  - when
    ```cpp
    #include <gtest/gtest.h>
    ```
  - actual
    ```
    warning C4996: 'std::tr1': warning STL4002: The non-Standard std::tr1 namespace and TR1-only machinery are deprecated and will be REMOVED. You can define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING to acknowledge that you have received this warning.
    ```
  - howto
    1. goto
       1. Project Properties
       2. C/C++
       3. Preprocessor
       4. Preprocessor Definitions
    2. add ``_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING``
  - link
    - url: https://stackoverflow.com/questions/48091421/vs-2017-command-line-error-d8004
    - retrieved: 2023_06_22
