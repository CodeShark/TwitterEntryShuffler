# TwitterEntryShuffler
Random shuffler for twitter posts using the double sha256 of a nonce.

The ShuffleEntries.cpp file takes a list of tweet urls as input and outputs a file containing the user handles shuffled using a nonce constructed from the xor of a secret and a block hash. The secret and block hash in the ShuffleEntries.cpp file are just an example.

The double sha256 of the secret is 8dd4d706845ed329e7f4d3363f263e8e72d8d7b13c77dd1f4471f37c066b94ed.
The actual secret will be revealed after Bitcoin block 502961 is mined and the block hash of that block will be used to generate the nonce.

Best of luck to all entrants!
