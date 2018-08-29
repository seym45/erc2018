from scipy.interpolate import interp1d
import this
import constants


def base_angle(raw_value):
    return raw_value / 360


x_act1_dist = []
y_act1_angle = []
f_act1 = interp1d(x_act1_dist, y_act1_angle, kind='cubic')
def act1_angle(raw_dist):
    return f_act1(raw_dist)



x_act2_dist = []
y_act2_angle = []
f_act2 = interp1d(x_act2_dist, y_act2_angle, kind='cubic')
def act2_angle(raw_dist):
    return f_act2(raw_dist)


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
