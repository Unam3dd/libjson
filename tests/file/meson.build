#############################
#
#       BUILD TEST
#
#############################

TEST_FILE_SRCS = ['./test_file_1.c', './test_file_2.c']

test_file_1 = executable('test_file_1',
                files(TEST_FILE_SRCS[0]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)


test_file_2 = executable('test_file_2',
                files(TEST_FILE_SRCS[1]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('test file 1', test_file_1, args: ['../examples/test.json'], verbose: false, suite: ['file'])

test('test file 2', test_file_1, args: ['../examples/toto'], verbose: false, should_fail: true, suite: ['file'])

test('test file 3', test_file_2, args: ['../examples/toto'], verbose: false, should_fail: false, suite: ['file'])
