#!/bin/bash

# Test execution of a simple command
test_command_simple() {
    echo "Test: Simple command execution"
    ./minishell -c "/bin/ls"
}

# Test execution of a command with arguments
test_command_with_args() {
    echo "Test: Command with arguments"
    ./minishell -c "/bin/ls -l /"
    ./minishell -c "/bin/echo Hello World"
    ./minishell -c "/usr/bin/env"
}

# Test execution of different commands
test_different_commands() {
    echo "Test: Different commands"
    ./minishell -c "/bin/pwd"
    ./minishell -c "/usr/bin/whoami"
    ./minishell -c "/usr/bin/which ls"
}

# Test edge cases with non-existent commands
test_non_existent_command() {
    echo "Test: Non-existent command"
    ./minishell -c "/bin/nonexistent"
}

# Test repeated execution
test_repeated_execution() {
    echo "Test: Repeated execution"
    for i in {1..5}; do
        ./minishell -c "/bin/echo Test $i"
    done
}

# Execute all tests
run_tests() {
    test_command_simple
    test_command_with_args
    test_different_commands
    test_non_existent_command
    test_repeated_execution
}

run_tests
