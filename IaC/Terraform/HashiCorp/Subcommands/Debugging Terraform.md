Terraform has detailed logs which can be enabled by setting the `TF_LOG` environment variable to any value. This will cause detailed logs to appear on stderr.

You can set `TF_LOG` to one of the log levels `TRACE`, `DEBUG`, `INFO`, `WARN` or `ERROR` to change the verbosity of the logs.

Setting `TF_LOG` to `JSON` outputs logs at the `TRACE` level or higher, and uses a parseable JSON encoding as the formatting.

**Warning:** The JSON encoding of log files is not considered a stable interface. It may change at any time, without warning. It is meant to support tooling that will be forthcoming, and that tooling is the only supported way to interact with JSON formatted logs.

Logging can be enabled separately for terraform itself and the provider plugins using the `TF_LOG_CORE` or `TF_LOG_PROVIDER` environment variables. These take the same level arguments as `TF_LOG`, but only activate a subset of the logs.

To persist logged output you can set `TF_LOG_PATH` in order to force the log to always be appended to a specific file when logging is enabled. Note that even when `TF_LOG_PATH` is set, `TF_LOG` must be set in order for any logging to be enabled.

If you find a bug with Terraform, please include the detailed log by using a service such as gist.

### 🔹 Terraform Logging Overview

#### 1. Enable Logging

- Set the environment variable `TF_LOG` to activate logging.

```Bash
export TF_LOG=DEBUG
```

- Logs go to **stderr** by default.
#### 2. Log Levels

- `TRACE` → Most detailed (every function call, very noisy).
    
- `DEBUG` → Useful for troubleshooting providers/state issues.
    
- `INFO` → General useful messages.
    
- `WARN` → Warnings, potential issues.
    
- `ERROR` → Only serious failures.
    
- `JSON` → Same as `TRACE` but formatted in JSON. ⚠️ Not stable, only intended for tooling.

#### 3. Core vs Provider Logs

- `TF_LOG` → Enables logging globally (Terraform core + providers).
    
- `TF_LOG_CORE` → Logs **only Terraform core**.
    
- `TF_LOG_PROVIDER` → Logs **only providers**.
    

👉 Example:

```Bash
export TF_LOG_PROVIDER=DEBUG
export TF_LOG_CORE=ERROR
```

#### 4. Persist Logs to a File

- Use `TF_LOG_PATH` to save logs:

```Bash
export TF_LOG=DEBUG
export TF_LOG_PATH=terraform.log
```

Important: `TF_LOG_PATH` **requires** `TF_LOG` to be set, otherwise nothing is written.

#### 5. Sharing Logs

- If you find a bug, HashiCorp recommends sharing the **full log** (e.g., via Gist, Pastebin, etc.) since it contains details on what Terraform and providers were doing.

For **day-to-day debugging**, `TF_LOG=DEBUG` is usually enough.  
For **deep troubleshooting provider crashes**, `TF_LOG=TRACE` or `TF_LOG=JSON` can reveal hidden details — but they produce _very large_ logs.