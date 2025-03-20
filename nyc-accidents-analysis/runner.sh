input="gs://pbd-23-mk-01/project1/input/datasource1/"
input_2="gs://pbd-23-mk-01/project1/input/datasource4/"
output_mr="gs://pbd-23-mk-01/project1/final/mr/"
output="gs://pbd-23-mk-01/project1/final/output/"

mapred streaming \
-files mapper.py,reducer.py \
-input $input -output $output_mr \
-mapper mapper.py -reducer reducer.py

beeline -n ${USER} -u jdbc:hive2://localhost:10000/default \
--hivevar input_dir3=$output_mr \
--hivevar input_dir4=$input_2 \
--hivevar output_dir6=$output \
-f hive.sql
