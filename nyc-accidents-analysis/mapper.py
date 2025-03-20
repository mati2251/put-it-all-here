#!/bin/python

import sys
import time

for line in sys.stdin:
    data = line.strip().split(",")
    date_raw = data[0]
    date = time.strptime(date_raw, "%m/%d/%Y")
    zip_code = data[2]
    if date.tm_year <= 2012 or len(zip_code) == 0:
        continue
    street_ids = [6, 7, 8]
    accident_ids = [11, 12, 13, 14, 15, 16]
    accident_label = ["pedestrians-injured", "pedestrians-killed", "cyclist-injured", "cyclist-killed", "motorist-injured", "motorist-kille"]
    for street_id in street_ids:
        if len(data[street_id]) > 0:
            for i in range(len(accident_ids)):
                if int(data[accident_ids[i]]) > 0:
                    street = data[street_id].replace(" ", "_")
                    print(f"{zip_code}-{street}-{accident_label[i]}\t{data[accident_ids[i]]}")
