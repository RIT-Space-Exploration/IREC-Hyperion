nulldata_keys = []

lsm9ds1_keys = [
    None, None, None, #'accelX', 'accelY', 'accelZ',
    'gyroX', 'gyroY', 'gyroZ',
    'magX', 'magY', 'magZ'
]

bme280_keys = [
    'temp1',
    'pressure',
    'humidity',
    None, #'altitude'
]

ccs811_keys = [
    'co2', 'tvoc'
]

lis331_keys = [
    'accelX', 'accelY', 'accelZ'
]

pfsl_keys = [
    'altitude'
]

oren_keys = [
    'pitch',
    'roll',
    'yaw'
]

cmmd_keys = []

info_keys = [
    'text'
]

handler_keys = {
    0   : nulldata_keys,
    1   : lsm9ds1_keys,
    2   : bme280_keys,
    3   : ccs811_keys,
    4   : lis331_keys,
    5   : pfsl_keys,
    6   : oren_keys,
    7   : cmmd_keys,
    8   : info_keys
}

files = {
    -1  : 'all',
    0   : 'null',
    1   : 'lsm9ds1',
    2   : 'bme280',
    3   : 'ccs811',
    4   : 'lis331',
    5   : 'pfsl',
    6   : 'oren',
    7   : 'cmmd',
    8   : 'info'
}

def header_handler(header_lst):
    return int(header_lst[0]) , [ int(flag) for flag in header_lst[1:5] ] , int(header_lst[5])

def payload_builder(data_type, time, values):
    keys = handler_keys[data_type]
    payload = {}
    payload['timeStamp'] = time
    for idx,key in enumerate(keys):
        if key is not None:
            payload[key] = int(float(values[idx])) # num of values & keys should be the same
    return payload