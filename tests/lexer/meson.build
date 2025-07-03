#############################
#
#       BUILD TEST
#
#############################

TEST_LEXER_SRCS = [
  './test_lexer_1.c' 
  ]

test_lexer_1 = executable('test_lexer_1',
                files(TEST_LEXER_SRCS[0]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('test lexer 1', test_lexer_1, args: ['../examples/test.json'], verbose: false, suite: ['lexer'])

