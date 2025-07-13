# CashRegister - Data Representations
How is data stored in the CashRegister program?

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
with the given integer representing an equal percentage value.

The statement...
```c
unsigned short discount = 67;
```
...stores the value 67% in `discount`. 

Percentage values are stored as such to prevent the use of 
floating-point arithmetic during any given operation. To apply the given
percentage to a quantity of currency, perform...
```c
unsigned long price_diff = (discount * usd_value) / 100;
```

For simplicity, no rounding occurs. All values calculated using
this method are truncated, resulting in the loss of at most 1 cent.

## Text
### Currency
Currency is printed formatted as...
```
$[N,NN]N[.0N]
```
...where N represents a decimal digit, bracketed portions are optional, and 
$ represents the program's currency symbol. All quantities of currency
are positive; negative values are invalid. All quantities specifying
cents must be 2 digits long.

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
$[N,NN]N[.0N][xN]
```
...where the portion `[xN]` represents an optional multiplier.
Inputs with mulipliers are treated as though the resulting value
itself was entered. ie: the input `$8.06x4` is identical to the 
input `$32.24`. All multipliers must consist of a lowercase `x`
followed by any number of decimal digits. Fractional multipliers
are not allowed.
