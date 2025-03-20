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
output_file = f'charts_top_10_extended_new.csv'

newRows = []

df = pd.read_csv(input_file, low_memory=False)
ids = df.iloc[:, -1].values

step = 100

errors = []

for i in range(0, len(df), step):
    temp_ids = ids[i:i+step]
    audio_features = sp.audio_features(tracks=temp_ids)
    audio_features = [item for item in audio_features if item is not None]
    for j, temp_id in enumerate(temp_ids, start=i):
        try:
            print('.', end='')
            newRows.append(df.iloc[j, 0:7].values.tolist())
            audio_feature = [item for item in audio_features if item['id'] == temp_id][0]
            newRows[-1].append(audio_feature['acousticness'])
            newRows[-1].append(audio_feature['danceability'])
            newRows[-1].append(audio_feature['duration_ms'])
            newRows[-1].append(audio_feature['energy'])
            newRows[-1].append(audio_feature['instrumentalness'])
            newRows[-1].append(audio_feature['liveness'])
            newRows[-1].append(audio_feature['speechiness'])
            newRows[-1].append(audio_feature['tempo'])
        except:
            print(f"\nError at {j}")
            errors.append(j)

with open(output_file, 'w', newline='') as csv_output_file:
    writer = csv.writer(csv_output_file)
    writer.writerows(newRows)
print(errors)