import pymysql.cursors

# Connect to the database
connection = pymysql.connect(host='192.168.137.1',
                             user='erc',
                             password='erc',
                             db='erc')

connection.autocommit(True)


def read_angles():
    sql = "SELECT a1,a2,a3 FROM ikdata group by id desc limit 1"
    try:
        with connection.cursor() as cursor:
            cursor.execute(sql)
            result = cursor.fetchone()
            return [angle for angle in result]
    except Exception as e:
        print(e)


def read_command():
    sql = "SELECT cmd FROM command WHERE id = 1"
    try:
        with connection.cursor() as cursor:
            cursor.execute(sql)
            result = cursor.fetchone()
            return result[0]
    except Exception as e:
        print(e)


def store_angles(a1,a2,a3):
    sql = "INSERT INTO "
    sql += "`ikdata`"
    sql += "(`id`,`a1`,`a2`,`a3`,`a4`,`a5`,`a6`) VALUES (NULL,"
    sql +=  str(a1) + ','
    sql +=  str(a2) + ','
    sql +=  str(a3) + ',0,0,0)'
    try:
        # print(sql)
        with connection.cursor() as cursor:
            cursor.execute(sql)
        connection.commit()
    except Exception as e:
        print(e)

def read_targets():
    sql = "SELECT t1,t2,t3 FROM target"
    try:
        with connection.cursor() as cursor:
            cursor.execute(sql)
            result = cursor.fetchone()
            return [x for x in result]
    except Exception as e:
        # print(read_targets.__name__ + ": "+ str(e))
        pass
        


def delete_target():
    sql = "DELETE FROM `target` WHERE 1"
    try:
        with connection.cursor() as cursor:
            cursor.execute(sql)
    except Exception as e:
        print(e)

def store_command(command):
    sql = "UPDATE "
    sql += "`command`"
    sql += "SET cmd = "
    sql += "'" + command + "'"
    sql +=" WHERE id = 1"
    try:
        with connection.cursor() as cursor:
            cursor.execute(sql)
        connection.commit()
    except Exception as e:
        print(e)



def store_in_imu_test(data):
    sql = "INSERT INTO `"
    sql = sql + "`imu_test`" 
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

if __name__ == '__main__':
    # store_command('asasd ')
    # print(read_command())
    # sql = 'UPDATE target set t1=20 where t1=5'    
    
    # with connection.cursor() as cursor:
    #     cursor.execute(sql)

    # delete_target()    
    store_angles(10,10,10)
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
