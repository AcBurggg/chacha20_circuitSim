# chacha20_circuitSim
This is an implementation of the chacha20 block function.
It is designed to create a keystream of 512 bits given an input of sixteen 32 bit words.
- the first four words are "expand 32-byte k" in ASCII
- the next eight words are the secret key 
- the next two words are the counter
- the last two words are the nonce

The keystream can then be XOR'd with a message to encrypt and XOR'd with a ciphertext to decrypt. 
