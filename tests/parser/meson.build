#############################
#
#       BUILD TEST
#
#############################

TEST_PARSER_SRCS = [
  './test_parser_test_1.c'
  ]

test_parser_test_1 = executable('test_parser_1',
                files(TEST_PARSER_SRCS[0]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('parser test 1', test_parser_test_1, args: ['../examples/test.json'], verbose: false, suite: ['parser'])

