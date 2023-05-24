import os
import random

gn_prefixes = ["The ", "A ", ""]
gn_adjectives = ["Black ", "White ", "Feral ", "Brutal ", "Unholy ", "Holy ", "Legendary ", "Calm ", "Furious ", "Brave ", "Majestic ", "Gloomy ", "Vibrant ", "Whispering ", "Enchanted ", "Mysterious ", "Radiant ", "Savage ", "Tranquil ", "Glistening ", "Eternal ", "Magical ", "Serene ", "Spectacular ", "Fearless ", "Glorious ", "Wild ", "Misty ", "Silent ", "Fierce ", "Dazzling ", "Ancient ", "Awe-inspiring ", "Grim ", "Enigmatic ", "Harmonious ", "Resplendent ", "Boundless ", "Alluring ", "Untamed ", "Noble ", "Supreme ", "Peaceful ", "Raging ", "Celestial ", "Imposing ", "Breathtaking ", "Solemn ", "Vivid ", "Fathomless ", "Unforgiving ", "Surreal ", "Majestic ",
                 "Everlasting ", "Epic ", "Stormy ", "Untouched ", "Roaring ", "Vast ", "Untamed ", "Magnificent ", "Fiery ", "Gentle ", "Unyielding ", "Captivating ", "Distant ", "Ethereal ", "Harsh ", "Spellbinding ", "Mythical ", "Immaculate ", "Transcendent ", "Boundless ", "Endless ", "Untrodden ", "Mesmerizing ", "Enchanting ", "Primeval ", "Mighty ", "Dynamic ", "Peerless ", "Grand ", "Mystical ", "Thundering ", "Stunning ", "Rugged ", "Cascading ", "Infinite ", "Luminous ", "Evolving ", "Unblemished ", "Solitary ", "Roaming ", "Serenading ", "Uncharted ", "Stellar ", "Enthralling ", "Renowned ", "Unspoiled ", "Picturesque ", "Radiant ", "Undying ", "Rapturous ", "Astonishing ", "Epic "]
gn_names = ["Sword ", "Soldier ", "Eagle ", "Tribe ", "Legion ",
            "Warfare ", "City ", "Rampage ", "Khan ", "Player ", "Bogalz ", "Dhaz ", "Das ", "Doggo ", "Cat ", "Luas ", "Gol ", "Neymar ", "Ugo ", "Losano "]
gn_connectors = ["of ", ""]
gn_ofsequels = ["Murcia", "Detroit", "Oklahoma", "Tokyo", "Beijing", "Blackburn", "Mars", "Rome", "Greece", "Lesoto", "London", "Paris", "New York City", "Los Angeles", "Chicago", "Toronto", "Sydney", "Melbourne", "Rio de Janeiro", "Moscow", "Berlin", "Madrid", "Barcelona", "Amsterdam", "Stockholm", "Copenhagen", "Oslo", "Dubai", "Istanbul", "Cairo", "Mumbai", "Bangkok", "Singapore", "Seoul", "Shanghai", "Hong Kong", "Buenos Aires", "São Paulo", "Mexico City", "Lima", "Cape Town", "Nairobi", "Marrakech", "Copenhagen", "Helsinki", "Reykjavik", "Athens", "Dublin", "Riga",
                "Prague", "Warsaw", "Vienna", "Budapest", "Brussels", "Zurich", "Stockholm", "Lisbon", "Brasília", "Bogotá", "Caracas", "Santiago", "Montreal", "Vancouver", "San Francisco", "Seattle", "Dublin", "Florence", "Venice", "Athens", "Istanbul", "Bangkok", "Sydney", "Seoul", "Riyadh", "Doha", "Nairobi", "Abuja", "Casablanca", "Manila", "Jakarta", "Ho Chi Minh City", "Kuala Lumpur", "New Delhi", "Tokyo", "Beijing", "Havana", "Cairo", "Marrakech", "Lima", "La Paz", "Santo Domingo", "San Juan", "San José", "Helsinki", "Prague", "Budapest", "Vienna", "Warsaw", "Rome"]
gn_emptysequels = ["I", "II", "III", "IV", "V", "VI",
                   "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX"]

total_testcases = 10000

# Create the 'testcases' directory if it doesn't exist
if not os.path.exists('testcases'):
    os.makedirs('testcases')

for i in range(1, total_testcases + 1):
    inputs = random.randint(20, 10000)
    # File path with the current testcase number
    filename = f"testcases/input{i}.txt"

    with open(filename, 'w') as file:
        for _ in range(inputs):
            genres = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
            prefix = random.choice(gn_prefixes)
            adjective = random.choice(gn_adjectives)
            name = random.choice(gn_names)
            connector = random.choice(gn_connectors)
            finals = random.choice(
                gn_ofsequels) if connector == "of " else random.choice(gn_emptysequels)
            downloads = random.randint(1000, 750000)
            totalGenres = random.randint(1, 6)
            selectedGenres = []

            for j in range(totalGenres):
                chosenGenre = random.choice(genres)
                selectedGenres.append(chosenGenre)
                genres.remove(chosenGenre)

            review = random.randint(1, 5)
            agerestriction = random.randint(1, 6)

            genres_string = ' '.join(str(num) for num in selectedGenres)

            file.write("1\n")
            file.write(prefix + adjective + name + connector + finals + "\n")
            file.write(str(downloads) + "\n")
            file.write(genres_string + "\n")
            file.write(str(review) + "\n\n")
            file.write(str(agerestriction) + "\n\n")

        file.write("3\n")
