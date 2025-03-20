-- parameters: 
-- 1. input_dir3: input data from mapreduce
-- 3. input_dir4: input data (postcode with district)
-- 2. output_dir6: output data for hive

create external table if not exists accidents (zip_code string, street string, accident_type string, killed_injured string, count int)
row format serde 'org.apache.hadoop.hive.serde2.RegexSerDe'
with serdeproperties (
"input.regex" = "(.*)-(.*)-(.*)-(.*)\t(.*)"
)
location '${input_dir3}';

load data inpath '${input_dir3}' into table accidents;


create external table if not exists postcode_district (postcode string, district string)
row format delimited fields terminated by ','
location '${input_dir4}';

load data inpath '${input_dir4}' into table postcode_district;

create table if not exists accidents_top3 (
street string,
person_type string,
killed int,
injured int
)
ROW FORMAT SERDE
'org.apache.hadoop.hive.serde2.JsonSerDe'
STORED AS TEXTFILE
location '${output_dir6}';

insert overwrite table accidents_top3
select street, accident_type as person_type, killed, injured  from (
select 
    a.street, a.accident_type,
    sum(case when a.killed_injured = 'injured' then a.count else 0 end) as injured,
    sum(case when a.killed_injured = 'kille' then a.count else 0 end) as killed,
    rank() over (partition by a.accident_type order by 
        sum(case when a.killed_injured = 'injured' then a.count else 0 end) + sum(case when a.killed_injured = 'kille' then a.count else 0 end) desc) as rnk
from 
    accidents a
left join 
    postcode_district p 
on 
    a.zip_code = p.postcode 
where 
    p.district = 'MANHATTAN'
group by 
    a.street, a.accident_type
order by 
    street
) ranked_data
where 
    rnk <= 3
order by
    accident_type, rnk;

