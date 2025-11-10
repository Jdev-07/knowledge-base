
The `terraform validate` command validates the configuration files in a directory, referring only to the configuration and not accessing any remote services such as remote state, provider APIs, etc.

Validate runs checks that verify whether a configuration is syntactically valid and internally consistent, regardless of any provided variables or existing state. It is thus primarily useful for general verification of reusable modules, including correctness of attribute names and value types.

It is safe to run this command automatically, for example as a post-save check in a text editor or as a test step for a re-usable module in a CI system.

Validation requires an initialized working directory with any referenced plugins and modules installed. To initialize a working directory for validation without accessing any configured backend, use:

```Bash
terraform init -backend=false
```

To verify configuration in the context of a particular run (a particular target workspace, input variable values, etc), use the terraform plan command instead, which includes an implied validation check.

## Usage

Usage: `terraform validate [options]`

This command accepts the following options:

- 
    
    [`-json`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#json) - Produce output in a machine-readable JSON format, suitable for use in text editor integrations and other automated systems. Always disables color.
    
- 
    
    [`-no-color`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#no-color) - If specified, output won't contain any color.

## JSON Output Format

When you use the `-json` option, Terraform will produce validation results in JSON format to allow using the validation result for tool integrations, such as highlighting errors in a text editor.

As with all JSON output options, it's possible that Terraform will encounter an error prior to beginning the validation task that will thus not be subject to the JSON output setting. For that reason, external software consuming Terraform's output should be prepared to find data on stdout that _isn't_ valid JSON, which it should then treat as a generic error case.

The output includes a `format_version` key, which as of Terraform 1.1.0 has value `"1.0"`. The semantics of this version are:

- We will increment the minor version, e.g. `"1.1"`, for backward-compatible changes or additions. Ignore any object properties with unrecognized names to remain forward-compatible with future minor versions.
- We will increment the major version, e.g. `"2.0"`, for changes that are not backward-compatible. Reject any input which reports an unsupported major version.

We will introduce new major versions only within the bounds of [the Terraform 1.0 Compatibility Promises](https://developer.hashicorp.com/terraform/language/v1.1.x/v1-compatibility-promises).

In the normal case, Terraform will print a JSON object to the standard output stream. The top-level JSON object will have the following properties:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`valid`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#valid) (boolean): Summarizes the overall validation result, by indicating `true` if Terraform considers the current configuration to be valid or `false` if it detected any errors.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`error_count`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#error_count) (number): A zero or positive whole number giving the count of errors Terraform detected. If `valid` is `true` then `error_count` will always be zero, because it is the presence of errors that indicates that a configuration is invalid.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`warning_count`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#warning_count) (number): A zero or positive whole number giving the count of warnings Terraform detected. Warnings do not cause Terraform to consider a configuration to be invalid, but they do indicate potential caveats that a user should consider and possibly resolve.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`diagnostics`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#diagnostics) (array of objects): A JSON array of nested objects that each describe an error or warning from Terraform.
    

The nested objects in `diagnostics` have the following properties:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`severity`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#severity) (string): A string keyword, currently either `"error"` or `"warning"`, indicating the diagnostic severity.
    
    The presence of errors causes Terraform to consider a configuration to be invalid, while warnings are just advice or caveats to the user which do not block working with the configuration. Later versions of Terraform may introduce new severity keywords, so consumers should be prepared to accept and ignore severity values they don't understand.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`summary`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#summary) (string): A short description of the nature of the problem that the diagnostic is reporting.
    
    In Terraform's usual human-oriented diagnostic messages, the summary serves as a sort of "heading" for the diagnostic, printed after the "Error:" or "Warning:" indicator.
    
    Summaries are typically short, single sentences, but can sometimes be longer as a result of returning errors from subsystems that are not designed to return full diagnostics, where the entire error message therefore becomes the summary. In those cases, the summary might include newline characters which a renderer should honor when presenting the message visually to a user.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`detail`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#detail) (string): An optional additional message giving more detail about the problem.
    
    In Terraform's usual human-oriented diagnostic messages, the detail provides the paragraphs of text that appear after the heading and the source location reference.
    
    Detail messages are often multiple paragraphs and possibly interspersed with non-paragraph lines, so tools which aim to present detail messages to the user should distinguish between lines without leading spaces, treating them as paragraphs, and lines with leading spaces, treating them as preformatted text. Renderers should then soft-wrap the paragraphs to fit the width of the rendering container, but leave the preformatted lines unwrapped.
    
    Some Terraform detail messages currently contain an approximation of bullet lists using ASCII characters to mark the bullets. This is not currently a contractural formatting convention and so renderers should avoid depending on it and should instead treat those lines as either paragraphs or preformatted text per the rules above. A future version of this format may define some additional rules for processing other text conventions, but will do so within the bounds of the rules above to achieve backward-compatibility.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`range`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#range) (object): An optional object referencing a portion of the configuration source code that the diagnostic message relates to. For errors, this will typically indicate the bounds of the specific block header, attribute, or expression which was detected as invalid.
    
    A source range is an object with a property `filename` which gives the filename as a relative path from the current working directory, and then two properties `start` and `end` which are both themselves objects describing source positions, as described below.
    
    Not all diagnostic messages are connected with specific portions of the configuration, so `range` will be omitted or `null` for diagnostic messages where it isn't relevant.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`snippet`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#snippet) (object): An optional object including an excerpt of the configuration source code that the diagnostic message relates to.
    
    The snippet information includes:
    
    - [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
        
        [`context`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#context) (string): An optional summary of the root context of the diagnostic. For example, this might be the resource block containing the expression which triggered the diagnostic. For some diagnostics this information is not available, and then this property will be `null`.
        
    - [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
        
        [`code`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#code) (string): A snippet of Terraform configuration including the source of the diagnostic. This can be multiple lines and may include additional configuration source code around the expression which triggered the diagnostic.
        
    - [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
        
        [`start_line`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#start_line) (number): A one-based line count representing the position in the source file at which the `code` excerpt begins. This is not necessarily the same value as `range.start.line`, as it is possible for `code` to include one or more lines of context before the source of the diagnostic.
        
    - [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
        
        [`highlight_start_offset`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#highlight_start_offset) (number): A zero-based character offset into the `code` string, pointing at the start of the expression which triggered the diagnostic.
        
    - [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
        
        [`highlight_end_offset`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#highlight_end_offset) (number): A zero-based character offset into the `code` string, pointing at the end of the expression which triggered the diagnostic.
        
    - [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
        
        [`values`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#values) (array of objects): Contains zero or more expression values which may be useful in understanding the source of a diagnostic in a complex expression. These expression value objects are described below.

### 🗂️ Structure of JSON Output

Here’s what the top-level object looks like:

- **`valid` (bool)** → true if config is valid, false otherwise.
    
- **`error_count` (number)** → how many errors were found.
    
- **`warning_count` (number)** → how many warnings were found.
    
- **`diagnostics` (array)** → list of all errors/warnings with details.
    

Each diagnostic object can include:

- **`severity`** → `"error"` or `"warning"`.
    
- **`summary`** → short one-line description.
    
- **`detail`** → longer explanation, can include paragraphs or formatted text.
    
- **`range`** → (optional) where in the code the issue occurred (filename, start/end line & column).
    
- **`snippet`** → (optional) snippet of the code around the error with highlighting metadata.
    
- **`values`** → (optional) captured values to help debugging complex expressions.

```JSON
{
  "format_version": "1.0",
  "valid": false,
  "error_count": 1,
  "warning_count": 0,
  "diagnostics": [
    {
      "severity": "error",
      "summary": "Unsupported argument",
      "detail": "An argument named \"imag\" is not expected here. Did you mean \"image\"?",
      "range": {
        "filename": "main.tf",
        "start": { "line": 7, "column": 3 },
        "end": { "line": 7, "column": 8 }
      },
      "snippet": {
        "context": "resource \"azurerm_linux_virtual_machine\" \"vm\"",
        "code": "  imag = \"UbuntuLTS\"",
        "start_line": 7,
        "highlight_start_offset": 2,
        "highlight_end_offset": 6
      }
    }
  ]
}

```

### Source Position

A source position object, as used in the `range` property of a diagnostic object, has the following properties:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`byte`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#byte) (number): A zero-based byte offset into the indicated file.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`line`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#line) (number): A one-based line count for the line containing the relevant position in the indicated file.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`column`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#column) (number): A one-based count of _Unicode characters_ from the start of the line indicated in `line`.
    

A `start` position is inclusive while an `end` position is exclusive. The exact positions used for particular error messages are intended for human interpretation only and subject to change in future versions of Terraform due either to improvements to the error reporting or changes in implementation details of the language parser/evaluator.

### Expression Value

An expression value object gives additional information about a value which is part of the expression which triggered the diagnostic. This is especially useful when using `for_each` or similar constructs, in order to identify exactly which values are responsible for an error. The object has two properties:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`traversal`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#traversal) (string): An HCL-like traversal string, such as `var.instance_count`. Complex index key values may be elided, so this will not always be valid, parseable HCL. The contents of this string are intended to be human-readable and are subject to change in future versions of Terraform.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#)
    
    [`statement`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/validate#statement) (string): A short English-language fragment describing the value of the expression when the diagnostic was triggered. The contents of this string are intended to be human-readable and are subject to change in future versions of Terraform.

### **Expression Value**

Sometimes the error is caused by a **variable or value** (not just the line). Expression value helps you understand **which input caused the problem**.

It has:

- **traversal** → Shows the exact variable/path, like `var.instance_count` or `aws_instance.myserver.id`.
    
- **statement** → A short explanation of the value at the moment of the error (for example, “was null” or “was 3”).

```CSharp
Error: Invalid for_each argument
  on main.tf line 10, in resource "aws_instance" "example":
  var.servers was empty list
```