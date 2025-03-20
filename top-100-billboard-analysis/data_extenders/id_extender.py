import spotipy
import csv
import sys
from dotenv import dotenv_values
from spotipy.oauth2 import SpotifyClientCredentials

arguments = sys.argv
start = int(arguments[1])
end = int(arguments[2])

env_vars = dotenv_values('.env')

CLIENT_ID = env_vars.get('SPOTIFY_APP_ID')
CLIENT_SECRET = env_vars.get('SPOTIFY_APP_SECRET')

sp = spotipy.Spotify(auth_manager=SpotifyClientCredentials(client_id=CLIENT_ID,
                                                           client_secret=CLIENT_SECRET))

input_file = 'charts_top_10.csv'
output_file = f'charts_extended/charts_top_10_extended{start}-{end}.csv'


with open(input_file, 'r') as csv_input_file:
    reader = csv.reader(csv_input_file)
    rows = list(reader)

newRows = []

for i, row in enumerate(rows[start:], start=start):
    print(i)
    artist = row[3]
    if('Featuring' in artist):
        artist = artist.split('Featuring')[0]
    if('&' in artist):
        artist = artist.split('&')[0]
    if(' x ' in artist):
        artist = artist.split(' x ')[0]
    if('(' in artist):
        artist = artist.split(' (')[0]
    track = row[2]
    if('/' in track):
        track = track.split('/')[0]
    if('(' in track):
        track = track.split('(')[0]

    try:
        result = sp.search(q=f"artist:{artist} track:{track}", type="track", limit=1)
        if(result['tracks']['total'] == 0):
            result = sp.search(q=f"track:{track}", type="track", limit=1)
        if(result['tracks']['total'] == 0 and '\'' in track):
            track = track.replace('\'', '')
            result = sp.search(q=f"artist:{artist} track:{track}", type="track", limit=1)
        newRows.append(row)
        newRows[-1].append(result['tracks']['items'][0]['id'])
        
    except:
        print(f"Error at {i}")
        output_file = f'charts_extended/charts_top_10_extended{start}-{i}.csv'
        print(row)
        break

    if(i>=end):
        break
print("DONE")

with open(output_file, 'w', newline='') as csv_output_file:
    writer = csv.writer(csv_output_file)
    writer.writerows(newRows)
    