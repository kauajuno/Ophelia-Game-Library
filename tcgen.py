import os
import random

gn_prefixes = ["The ", "A ", ""]
gn_adjectives = ["Black ", "White ", "Feral ", "Brutal ", "Unholy ", "Holy ", "Legendary ", "Calm ", "Furious ", "Brave "]
gn_names = ["Sword ", "Soldier ", "Eagle ", "Tribe ", "Legion ", "Warfare ", "City ", "Rampage ", "Khan ", "Player "]
gn_connectors = ["of ", ""]
gn_ofsequels = ["Detroit", "Oklahoma", "Tokyo", "Beijing", "Blackburn", "Mars", "Rome", "Greece", "Lesoto"]
gn_emptysequels = ["I", "II", "III", "IV", "V"]

total_testcases = 10000

# Create the 'testcases' directory if it doesn't exist
if not os.path.exists('testcases'):
    os.makedirs('testcases')

for i in range(1, total_testcases + 1):
    inputs = random.randint(4, 10000)
    filename = f"testcases/input{i}.txt"  # File path with the current testcase number

    with open(filename, 'w') as file:
        for _ in range(inputs):
            genres = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
            prefix = random.choice(gn_prefixes)
            adjective = random.choice(gn_adjectives)
            name = random.choice(gn_names)
            connector = random.choice(gn_connectors)
            finals = random.choice(gn_ofsequels) if connector == "of " else random.choice(gn_emptysequels)
            downloads = random.randint(1000, 750000)
            totalGenres = random.randint(1, 7)
            selectedGenres = []

            for j in range(totalGenres):
                chosenGenre = random.choice(genres)
                selectedGenres.append(chosenGenre)
                genres.remove(chosenGenre)

            review = random.randint(1, 6)
            agerestriction = random.randint(1, 7)

            genres_string = ' '.join(str(num) for num in selectedGenres)

            file.write("1\n")
            file.write(prefix + adjective + name + connector + finals + "\n")
            file.write(str(downloads) + "\n")
            file.write(genres_string + "\n")
            file.write(str(review) + "\n")
            file.write(str(agerestriction) + "\n")

        file.write("3")

