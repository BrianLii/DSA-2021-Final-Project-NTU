# DSA 2021 Final Project

**Team ID: Team 37**  
**Student IDs: B09902054, B09902061, B09902105**

## Run the Project

1. **Download the Data:**
   - If you do not have `gdown` installed:
     - Manually download the following files from Google Drive:
       - [`mail_data.tar.gz`](https://drive.google.com/file/d/1-GPVynhpkj8gJseWnsxFBKn_YXyuxCDi/view?usp=sharing)
       - [`test_data.zip`](https://drive.google.com/file/d/1-0ONMtK8khrYSwl7Xe8HM9i9vpnx94mI/view?usp=sharing)
     - Extract and organize the files using the following commands:
       ```bash
       tar -xvzf mail_data.tar.gz
       mv test_data mail_data
       unzip test_data.zip
       ```
   - Alternatively, if you have `gdown` installed, download the files using the Makefile:
     ```bash
     make download
     ```

2. **Run the Tests:**
   Execute the following command to run the tests:
   ```bash
   make test
   ```