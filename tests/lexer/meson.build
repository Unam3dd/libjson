#############################
#
#       BUILD TEST
#
#############################

TEST_LEXER_SRCS = [
  './test_lexer_2.c',
  './test_lexer_3.c',
  './test_lexer_4.c'
  ]

test_lexer_2 = executable('test_lexer_2',
                files(TEST_LEXER_SRCS[0]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)


test_lexer_3 = executable('test_lexer_3',
                files(TEST_LEXER_SRCS[1]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_lexer_4 = executable('test_lexer_4',
                files(TEST_LEXER_SRCS[2]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('test lexer 2', test_lexer_2, verbose: false, suite: ['lexer'])
test('test lexer 3', test_lexer_3, verbose: false, suite: ['lexer'])
test('test lexer 4', test_lexer_4, verbose: false, suite: ['lexer'])

