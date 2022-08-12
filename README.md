# Cachat
Bytecode-Language, highly modular

## Usage
`-f filename`
Specify the file to run 

## Behavior

### Security Guarantees
CACHAT will not terminate the program by itself

## Opcodes Table
| opcode | title | arguments (4b or empty)| Description | 
| ---    | ---   | ---           | ---         |
| 0x00   | exit  | exit code     | Performs sys_exit | 
| 0x01   | jmp   | address       | Performs a simple jump to the address, without side-effects |
| 0x02   | mv_reg| value         | moves <value> into data register |
| 0x03 | push | -- | put register into stack - register data persists |
| 0x04 | push | value | put value into stack |
| 0x05 | pop | -- | pops stack to register | 


| 0xFF   | ext   | sys_call (1b + 4b argument)      | for extended system-call codes. These also get 4b of argument spaces if needed |
| 0xFF + 0x00 | debug | no Argument | prints out some debugging information | 

## cachat-Calls
| Call-ID | Title | Registers | Description