import pymysql.cursors

# Connect to the database
connection = pymysql.connect(host='localhost',
                             user='root',
                             password='',
                             db='erc2018')


def store(table_name, data):
    sql = "INSERT INTO `"
    sql = sql + table_name 
    sql = sql +  "`(`id`, `ax`, \
    `ay`, `az`, `gx`, `gy`, `gz`, `roll`, `pitch`, `yaw`,\
    `encoder1`, `encoder2`, `time2process`) VALUES (NULL,"
    for value in data.split(','):
        sql = sql + "'" + value + "',"
    sql = sql + "'1', '1', '1'"
    sql = sql + ");"
    try:
        print(sql)
        with connection.cursor() as cursor:
            cursor.execute(sql)
        connection.commit()
    except Exception as e:
        print(e)

# try:
#     # with connection.cursor() as cursor:
#     #     # Create a new record
#     #     sql = "INSERT INTO `users` (`email`, `password`) VALUES (%s, %s)"
#     #     cursor.execute(sql, ('webmaster@python.org', 'very-secret'))

#     # # connection is not autocommit by default. So you must commit to save
#     # # your changes.
#     # connection.commit()

#     with connection.cursor() as cursor:
#         # Read a single record
#         sql = "SELECT * FROM imu_test"
#         cursor.execute(sql)
#         result = cursor.fetchone()
#         print(result)
#         result = cursor.fetchone()
#         print(result)
#         result = cursor.fetchone()
#         print(result)
#         result = cursor.fetchone()
#         print(result)
# finally:
#     connection.close()


#     # INSERT INTO `imu_test` (`id`, `ax`, `ay`, `az`, `gx`, `gy`, `gz`, `roll`, `pitch`, `yaw`, `encoder1`, `encoder2`, `time2process`) VALUES (NULL, '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1');

if __name__ == '__main__':
    store('imu_test', '1.00,-0.10,0.07,1.71,-0.24,-0.31,-172.54,84.16,163.74')
    store('imu_test', '1.00,-0.10,0.07,1.71,-0.24,-0.31,-172.54,84.16,163.75')