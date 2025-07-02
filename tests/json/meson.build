#############################
#
#       BUILD TEST
#
#############################

TEST_JSON_SRCS = [
  './test_json_1.c', 
  './test_json_2.c', 
  './test_json_3.c', 
  './test_json_4.c',
  './test_json_5.c',
  './test_json_6.c'
  ]

test_json_1 = executable('test_json_1',
                files(TEST_JSON_SRCS[0]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)


test_json_2 = executable('test_json_2',
                files(TEST_JSON_SRCS[1]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)


test_json_3 = executable('test_json_3',
                files(TEST_JSON_SRCS[2]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_json_4 = executable('test_json_4',
                files(TEST_JSON_SRCS[3]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_json_5 = executable('test_json_5',
                files(TEST_JSON_SRCS[4]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_json_6 = executable('test_json_6',
                files(TEST_JSON_SRCS[5]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test('test json 1', test_json_1, verbose: false, suite: ['json'])
test('test json 2', test_json_2, verbose: false, suite: ['json'])
test('test json 3', test_json_3, verbose: false, suite: ['json'])
test('test json 4', test_json_4, verbose: false, suite: ['json'])
test('test json 5', test_json_5, verbose: false, suite: ['json'])
test('test json 6', test_json_6, verbose: false, suite: ['json'])

