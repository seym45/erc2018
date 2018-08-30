from scipy.interpolate import interp1d
import constants


def base_angle(raw_value):
    return raw_value/360

# x_act1_dist = [318, 770, 1160, 1260, 1580, 1675, 1900]
# y_act1_angle = [68 ,75, 100, 110, 123, 132, 153]
# f_act1 = interp1d(x_act1_dist, y_act1_angle, kind='cubic')
def act1_angle(raw_dist):
    # if raw_dist < x_act1_dist[0]:
    #     temp = y_act1_angle[0]
    # elif raw_dist < x_act1_dist[len(x_act1_dist)-1]:
    #     temp = y_act1_angle[len(y_act1_angle)-1]
    # else:
    #     temp = f_act1(raw_dist)
    return 0



x_act2_dist = [318, 770, 1160, 1260, 1580, 1675, 1900]
y_act2_angle = [68 ,75, 100, 110, 123, 132, 153]
f_act2 = interp1d(x_act2_dist, y_act2_angle, kind='cubic')
def act2_angle(raw_dist):
    if raw_dist < x_act2_dist[0]:
        temp = y_act2_angle[0]
    elif raw_dist < x_act2_dist[len(x_act2_dist)-1]:
        temp = y_act2_angle[len(y_act2_angle)-1]
    else:
        temp = f_act2(raw_dist)
    return temp


def roll_angle(raw_value):
    return raw_value / 360


def pitch_angle(raw_value):
    return raw_value / 360


list_of_get_angles = [
    base_angle,
    act1_angle,
    act2_angle,
    roll_angle,
    pitch_angle,
    ]

def get_angle(arm_name, raw_value):
    return list_of_get_angles[arm_name](raw_value)

if __name__ == '__main__':
    pass