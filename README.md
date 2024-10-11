# SAE102

Cette repo est pour la SAE 1.02 à l'IUT.

Il y a trois dossiers. (un par système de vote)

Chaque dossier est un projet QTCreator.

Demandez moi sur Discord pour savoir comment y ajouter votre dossier de projet QTCreator


# Documentation of functions in system1

## `generateRandVotes`

Generates a text file (`votes.txt`) containing random votes for each voter. The file lists the name of the candidate each voter selects.

### Parameters:
- `candidates`: A reference to a vector of strings containing the names of the candidates.
- `voters_cnt`: A reference to an unsigned integer representing the number of voters.

### Behavior:
- Uses a random number generator ([mt19937](https://cplusplus.com/reference/random/mt19937/)) seeded with the system's nanosecond clock to randomly select a candidate for each voter.
- Writes each randomly selected vote into the `votes.txt` file.
- Closes the file once all votes are recorded.

---

## `countVotes`

Counts the number of votes each candidate received from the `votes.txt` file.

### Parameters:
- `candidates`: A reference to a vector of strings containing the names of the candidates.

### Returns:
- A vector of unsigned integers representing the number of votes for each candidate, in the same order as the candidates appear in the input vector so they have corresponding index.

### Behavior:
- Reads the `votes.txt` file line by line.
- For each line (vote), increments the corresponding candidate's vote count.
- Returns a vector containing the total votes for each candidate.

---

## `getMaxIndice`

Finds the index of the highest value in a vector.

### Parameters:
- `Vect`: A vector containing the values to be evaluated.

### Returns:
- The index of the maximum value in the vector.

### Behavior:
- Iterates through the vector to find the maximum value.
- Returns the index corresponding to this maximum value.

---

## `getMaxValue`

Finds the maximum value in a vector.

### Parameters:
- `Vect`: A vector containing the values to be evaluated.

### Returns:
- The maximum value present in the vector.

### Behavior:
- Iterates through the vector to find and return the maximum value.

---

## `isTied`

Predicate that checks if two candidates are tied for the maximum number of votes.

### Parameters:
- `voteCounts`: A reference to a vector of unsigned integers containing the vote counts for each candidate.
- `max`: A reference to an unsigned integer containing the highest votes gotten by a candidate.

### Returns:
- `true` if two or more candidates have the same number of votes and the vote count equals `max`.
- `false` otherwise.

### Behavior:
- Iterates through the vote counts to check if two candidates are tied with the maximum vote count.
- **Note**: This function is unused.

---

## `isIn`

Predicate that checks if an element exists in a vector.

### Template Parameters:
- `Y`: The type of the element and the vector.

### Parameters:
- `element`: A reference to the element being searched for.
- `vect`: A reference to the vector in which to search for the element.

### Returns:
- `true` if the element is found in the vector.
- `false` otherwise.

### Behavior:
- Iterates through the vector to check if the element can be found.

---

## `getTies`

Returns a list of candidates who are tied for the highest number of votes.

### Parameters:
- `candidates`: A reference to a vector of strings containing the names of the candidates.
- `voteCounts`: A reference to a vector of unsigned integers containing the vote counts for each candidate.
- `max`: A reference to an unsigned integer containing the highest votes gotten by a candidate.

### Returns:
- A vector of strings containing the names of the tied candidates.

### Behavior:
- Iterates through the vote counts to find candidates who are tied and have the maximum number of votes and adds them using the `isIn` function to avoid adding duplicate candidates.

---

## `printVotes`

Prints the name of each candidate and their corresponding vote count to the console.

### Parameters:
- `candidates`: A constant reference to a vector of strings containing the names of the candidates.
- `votes`: A constant reference to a vector of unsigned integers containing the vote counts for each candidate.

### Behavior:
- Iterates through the candidates and prints each candidate's name along with their vote count in the format: `CandidateName : Votes`.

--- 

**Note**: There are many places where using a `std::map` would have been more efficient and optimized. However, I have yet to learn how to use them, and am too lazy to explain it to my group if I do learn how.

---