# Complex Types Overview

A complex type is a type that groups multiple values into a single value. Complex types are represented by type constructors, but several of them also have shorthand keyword versions.

There are two categories of complex types: collection type and structural types. 

## Collection Types

A collection type groups multiple values of one other type as a single one. The type of value within a collection is called `element type`. All collections must have an element type.

For example, the type `list(string)` means "list of strings". 

There are three kinds of collection type in the Terraform language

- `list(any)` 
- `map(any)`: a collection of values where each is identified by string label
- `set(any)`: a collection  of unique values that do not have any secondary identifiers or ordering. 

## Structural Types

A structural type allows multiple values of distinct types to be grouped together as a single value. Structural types require a schema as an argument to specify which types are allowed for which element

There are two kinds of structural type in the Terraform language:

- `object(any)`: a collection of named attributes that each have their type
- `tuple(any)`: a sequence of elements identified by consecutive whole numbers starting with zero, where each element has its own type.

Example of object:

```HCL
{
  name = "John"
  age  = 52
}
```

Example of a tuple

```HCL
["a", 15, true]
```


# Built-in Functions

