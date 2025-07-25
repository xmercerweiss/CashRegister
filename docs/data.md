# CashRegister - Data Representations
How is data stored in internally? What representations are valid?

## Numbers
### Currency
A quantity representing currency is stored as an `unsigned long`. 
Each increment of a variable of currency represents an increase equal to
1/100th of a unit of that currency. ie: if `usd_value` represents an 
amount of US dollars, then `usd_value++` adds one cent to that amount.

As such, the statement...
```c
unsigned long usd_value = 4508;
```
...means that `usd_value` represents $45.08.

### Percentages
A quantity representing a percentage is stored as an `unsigned short`,
with its value representing an equal percentage.

The statement...
```c
unsigned short discount = 67;
```
...stores the value 67% in `discount`. 

Percentage values are stored as such to prevent the use of 
floating-point arithmetic during any operation. 

Within all calculations, percentages are interpreted as the value
they hold (such as `50%`) applied to the running total of currency.
Assuming the current running total is `$6.50`, the input `+10%`
will add `$0.65` to the total, returning `$7.15`.

For simplicity, no rounding occurs. All values calculated using
this method are truncated, resulting in the loss of at most 1 cent.

## Text
### Currency
Currency is printed using the format...
```
$[N,NN]N[.0N]
```
...where N represents a decimal digit, bracketed portions are optional, and 
$ represents the program's currency symbol. All quantities of currency
are positive; negative values are invalid. Portions specifying cents are
optional, though they must have exactly 2 digits. 

The following are properly printed amounts of currency...
```
$100
$2,500
$9,000.10
$0.75
```

The following should never be printed...
```
-$5
$2500
$0.1
```

Currency is scanned formatted as...
```
[$NNN]N[.N][xN]
```
...where the portion `[xN]` represents an optional multiplier.
Inputs with mulipliers are treated as though the resulting value
itself was entered. ie: the input `$8.06x4` is identical to the 
input `$32.24`. All multipliers must consist of `x` or `X`
followed by any positive whole number less than 2^64. 

Currency signs are allowed, though not required, in currency inputs. While commas
are required in output, they are disallowed in input. Additionally, scanned quantities 
of currency may exclude additional zeros in the cents portion. While the string...

```
$200.1
```

...should never be printed, it's a valid input, and is interpreted as
`$200.10`.

### Percentages
Percentages are both printed and scanned in the format...
```
[NNN]N%
```
...where N is any decimal degit. Commas are not used to
separate groups of 1000s. All percentages must be positive
and less than 2^16. Multipliers on percentages are not allowed.
