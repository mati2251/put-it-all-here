# Building Info
## API
### BODY
Ciało zapytania powinno zawierać obiekt Lokacji JSON z następującymi polami:
- `name` - nazwa lokacji
- `id` - identyfikator lokacji (liczba całkowita)
- `type` - typ lokacji, dostepne typy: `ROOM`, `BUILDING`, `FLOOR`
Dla obiektów typu `ROOM`:
- `area` - powierzchnia w m^2
- `cube` - kubatura pomieszczenia w m^3
- `heating` - poziom zużycia energii ogrzewania
- `lighting` -  łączna moc oświetlenia
Dla obiektów typu `BUILDING` oraz `FLOOR`:
- `locations` - lista lokacji wchodzących w skład budynku/poziomu zgodna z powyższym opisem
#### Przykład
```json
{
    "name": "Budynek A",
    "id": 1,
    "type": "BUILDING",
    "locations": [
        {
            "name": "Piętro 1",
            "id": 2,
            "type": "FLOOR",
            "locations": [
                {
                    "name": "Sala 1",
                    "id": 3,
                    "type": "ROOM",
                    "area": 100,
                    "cube": 300,
                    "heating": 1000,
                    "lighting": 100
                },
                {
                    "name": "Sala 2",
                    "id": 4,
                    "type": "ROOM",
                    "area": 200,
                    "cube": 600,
                    "heating": 2000,
                    "lighting": 200
                }
            ]
        },
        {
            "name": "Piętro 2",
            "id": 5,
            "type": "FLOOR",
            "locations": [
                {
                    "name": "Sala 3",
                    "id": 6,
                    "type": "ROOM",
                    "area": 300,
                    "cube": 900,
                    "heating": 3000,
                    "lighting": 300
                },
                {
                    "name": "Sala 4",
                    "id": 7,
                    "type": "ROOM",
                    "area": 400,
                    "cube": 1200,
                    "heating": 4000,
                    "lighting": 400
                }
            ]
        }
    ]
}
```