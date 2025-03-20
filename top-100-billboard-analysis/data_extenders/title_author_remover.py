import csv
new_rows = []
with open('charts_top_10_ids.csv', 'r') as csv_input_file:
    reader = csv.reader(csv_input_file)
    rows = list(reader)
    for row in rows:
        if(len(row) >= 8):
            tmp_row = row[0:2]
            tmp_row.extend(row[-4:-1])
            tmp_row.append(row[-1])
        print(tmp_row)
        new_rows.append(tmp_row)
with open('charts_top_10_ids_new.csv', 'w', newline='') as csv_output_file:
    writer = csv.writer(csv_output_file)
    writer.writerows(new_rows)