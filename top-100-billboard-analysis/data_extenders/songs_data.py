import pandas as pd

df = pd.read_csv('./charts.csv')

df = df.groupby(['artist', 'song']).agg({'date': 'first','rank': 'min', 'weeks-on-board': 'max'}).reset_index()
print(df)
df.to_csv('./songs.csv', index=False)