
# Unit test mocks

Mocks are objects created to replace the real ones for the purpose of running unit tests.
Normally the elements to mock are dependencies of the code under test. This is, basically, a way
to limit the scope of the unit tests.

When creating mocks for your unit tests, there are 2 different concerns:

1. how to implement the mocks, and
2. how to replace the actual object with the mock

Here we are going to cover the second point.

**Note**: in order to run the examples described in the following sections, it is necessary to have installed the library [cmocka](https://cmocka.org)

## Java

In languages like Java, the replacement is achieved through polymorphism: the method
invoked is determined at runtime. Therefore, in Java parlance, the way to proceed would be something like:

- create a subclass of the object to be mocked
- override the method whose behaviour is to be changed
- inject this new object as a dependency into the production code instead of the real object

The specific details of how to do this depend on whether you are doing this manually
or with a framework like Spring (to inject the dependencies) or Mockito (to create the mocks)

## C

In C the approach is different as it is not object-oriented and there is no
polymorphism. Instead, the symbols to be used in a program are determined at link time.

As a result, in order to replace a symbol with a mock, we need to instruct the linker
to make that change. The details of how to do that vary with the platform.

**Note**: although it makes no difference for this discussion, the examples in this project use _cmocka_ to implement the mocks

### Apple

The linker allows the definition of aliases so that a symbol can be bound to another one. We can make use of this option to bind the real symbol to the one representing the mock.
Obviously, the change will affect the entire application, not only the test.

```
gcc -c test.c -o out/test.o
gcc -c timer.c -o out/timer.o
```

In Apple platform, symbols are prepended a '_' as can be easily verified with the commands:

```
nm out/test.o
nm out/timer.o
```

We need to take that into consideration when defining the alias:

```
gcc -Wl,-alias,___wrap_time,_time out/*.o -lcmocka -o out/test
```

### Linux

The GNU linker allows the definition of wrappers whereby `mysymbol` is resolved to
`__wrap_mysymbol` and the original function is made availabe with the name `__real_mysymbol`.

Therefore, we just need to define the behaviour of `__wrap_mysymbol`.

```
gcc -Wl,--wrap=time out/*.o -lcmocka -o out/test
```