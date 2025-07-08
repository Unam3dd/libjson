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
  './test_json_6.c',
  './test_json_7.c',
  './test_json_9.c',
  './test_json_10.c',
  './test_json_11.c',
  './test_json_12.c',
  './test_json_13.c'
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


test_json_7 = executable('test_json_7',
                files(TEST_JSON_SRCS[6]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)


test_json_9 = executable('test_json_9',
                files(TEST_JSON_SRCS[7]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_json_10 = executable('test_json_10',
                files(TEST_JSON_SRCS[8]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)


test_json_11 = executable('test_json_11',
                files(TEST_JSON_SRCS[9]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_json_12 = executable('test_json_12',
                files(TEST_JSON_SRCS[10]),
                c_args: ['-g', '-fPIC'],
                link_with: lib,
                include_directories: ['../../inc/', '.'],
                install: false,
                pie: true)

test_json_13 = executable('test_json_13',
                files(TEST_JSON_SRCS[11]),
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
test('test json 7', test_json_7, verbose: false, suite: ['json'])
test('test json 9', test_json_9, verbose: false, suite: ['json'])
test('test json 10', test_json_10, verbose: false, suite: ['json'])
test('test json 11', test_json_11, verbose: false, suite: ['json'])
test('test json 12', test_json_12, verbose: false, suite: ['json'])
test('test json 13', test_json_13, verbose: false, suite: ['json'])

