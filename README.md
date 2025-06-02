# chacha20_circuitSim Encryption

## User Guide
1. Traverse to ./IO directory

2. Update inputs.txt with your desired inputs. The default values represent the test vector found [here](https://www.rfc-editor.org/rfc/rfc7539#page-9). Your key should be 64 hex characters long for a total of 256 bits. Your counter should be 8 hex characters long. Your nonce should be 24 hex characters long. DO NOT DELETE THE START OF EACH LINE (i.e. "key: ", "counter: ", etc). Your user-inputted values should follow the same format as the example in which each set of eight hex characters has a space between it. [🚨WARNING WARNING WARNING🚨] If you change the key/counter/nonce values here, you will also need to update them in the main subcircuit of chacha20.sim. If you're trying to avoid tedious work, just leave these default values. 

3. Update line 4 of inputs.txt with a plaintext of your choosing. In other words, replace the [hello i'm andy] part with the string you'd like to encrypt. Again, do not delete the start of the line ("plaintext: ") Leave the quotation marks around your string. 

4. In this same directory, run the following command "./run.sh". Ensure that the directory now contains a file called "hexoutput.dat" and that the terminal is populated with some relevant information regarding your encrypting set-up/ expected ciphertext. 

5. Open chacha20.sim in circuitSim. On the subcircuit titled "main" find the ROM with the label "PLAINTEXT HERE!!". Right click it and select "load from file". Navigate to and select hexoutput.dat". 

6. Ensure that simulation is enabled in the file. Scroll down and find the set of 


## Fun Background Information
chacha20.sim can be opened using CS2110-CircuitSim.jar - a modification of the software found [here](https://github.com/ra4king/CircuitSim).

In this file is a circuitry implementation of the chacha20 block function as described in this [RFC document](https://www.rfc-editor.org/rfc/rfc7539). 
Note that a more broad overview can be found on the [Salsa20 wikipedia page](https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant). To the best of my
knowledge, the wikipedia page describes creator Daniel Bernstein's implementation while the RFC document (that I based my design on) is the IETF's modified
design. This slightly altered version decreases the length of the counter from 64-bits to 32-bits and increases the length of the nonce from 64-bits to 96-bits. 
Only the initial matrix state changes - the logic of the block_function is unchanged.

Currently, the "intitial state" of the input matrix is represented by 16 32-bit circuitSim constant pins at the top of the main subcircuit. The fields that can be altered are as follows: key0-key7, counter, and nonce0-2. The constant is a nothing-up-my-sleeve-number and should not be changed to maintain integriy. It is the ASCII value of "expand 32-byte k".

The block function's purpose is to generate a long keystream that can then be XOR'd with a plaintext input to get a ciphertext. Ciphers using this counter (CTR) mode of operation are thus quite similar to stream ciphers that use a one-time-pad. The "block" part is merely for generating the keystream. 

In addition to generating this keystream, the main subcircuit also supports the actual encryption process of a provided plaintext string on red hex displays. 

Currently, the circuitry is able to generate 512 bits of keystream at once meaning that strings to be encrypted should be limited to (512 / 8 bits per ascii char) 64 characters or fewer. In real life, the benefit of CTR would allow 2^32 * 512 bits to be generated easily by merely incrementing the counter value and running the block function again- this functionality has not (yet) been implemented in my .sim file. 
