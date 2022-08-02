# Welcome to My Blockchain
***

<img src="/https://github.com/Chrs-Clytn/my_blockchain/tree/main/.img/blocker.png" alt="Alt text" title="Blockchain Image">


## Task
Create a Blockchain from scratch!  


## Description
Blockchain is a command that allows for the creation and management of a blockchain. When the program starts (it loads a backup if there is one) then a prompt appears.  
This prompt allows to execute commands. When the commands are successful they display "ok" and if not, "nok: info" or info is an error message - see below:  

The blockchain prompt displays:  

a [ character  
a first letter that indicates the state of synchronization of the chain:  
"s" if the blockchain is synchronized  
"-" if the blockchain is not synchronized.  
n number of nodes in the chain.  
the "]> " string (with a space)  

[s3]>  

## Installation
gcl https://github.com/Chrs-Clytn/my_blockchain.git  

cd my_blockchain  

make  

./bin/my_blockchain  

## Usage
To add a nid identifier to the blockchain node : add node nid   

To remove nodes from the blockchain with a nid identifier. If nid is '*', all nodes are impacted : rm node nid...   

To add a bid identifier block to nodes identified by nid. If nid is '*', then all nodes are impacted : add block bid nid...  

To remove the bid identified blocks from all nodes where these blocks are present : rm block bid...  

To list all nodes by their identifiers. The option -l attaches the blocks bid's associated with each node : ls  

To synchronize all of the nodes with each other. Upon issuing this command, all of the nodes are composed of the same blocks : sync  

To save and leave the blockchain : quit  

## Contributors
Christopher Clayton  
Christian Badura  