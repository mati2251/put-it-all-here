import spotipy
import csv
import pandas as pd
from dotenv import dotenv_values
from spotipy.oauth2 import SpotifyClientCredentials


env_vars = dotenv_values('.env')

CLIENT_ID = env_vars.get('SPOTIFY_APP_ID')
CLIENT_SECRET = env_vars.get('SPOTIFY_APP_SECRET')

sp = spotipy.Spotify(auth_manager=SpotifyClientCredentials(client_id=CLIENT_ID,
                                                           client_secret=CLIENT_SECRET))

input_file = 'charts_top_10_extended.csv'
output_file = 'charts_top_10_extended_new.csv'

newRows = []

df = pd.read_csv(input_file, low_memory=False, delimiter=';')
ids = df.iloc[:, 5].values
step = 20

errors = []

for i in range(0, len(df), step):
    temp_ids = ids[i:i+step]
    tracks = sp.tracks(tracks=temp_ids)['tracks']
    for j, temp_id in enumerate(temp_ids, start=i):
        print(j)
        try:
            newRows.append(df.iloc[j, 0:-1].values.tolist())
            track = [item for item in tracks if item['id'] == temp_id][0]
            newRows[-1].append(track['name'])
            artists = ', '.join(list(map(lambda item: item['name'], track['artists'])))
            newRows[-1].append(artists)
        except:
            print(f"\nError at {j}")
            errors.append(j)

with open(output_file, 'w', newline='') as csv_output_file:
    writer = csv.writer(csv_output_file)
    writer.writerows(newRows)
print(errors)