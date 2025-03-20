import csv
file = 'charts_top_10.csv'
new_file = 'charts_top_10_new.csv'
with open (file, 'r') as f:
    csv_reader = csv.reader(f, delimiter=';')
    with open(new_file, 'w') as new_file:
        csv_writer = csv.writer(new_file, delimiter=',')
        for line in csv_reader:
            csv_writer.writerow(line)