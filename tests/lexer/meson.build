#############################
#
#       BUILD TEST
#
#############################

TEST_LEXER_SRCS = [
  './test_lexer_2.c'
  ]

test_lexer_2 = executable('test_lexer_2',
                files(TEST_LEXER_SRCS[0]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('test lexer 2', test_lexer_2, verbose: false, suite: ['lexer'])

