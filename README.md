# lambda-prism Project

The main aim of this project is to test AWS Lambda function with C++ runtime on Amazon Linux 2 VM. Want to call some solid modeling code to create a simple 3D prism. If this is working, will gain key first hand experience with Lambda function: 1. toolchain setup with legacy C++ libs. these C++ libs are valualbe and virtually impossible to redo with newer languages and developers; 2. lambda function delivery (size, lib list); 3. lambda cold start performance; 4. code performance; 5. input/output.
</p>
If the main aim is achieved, want to integrate this with other AWS services. 1. read/write input/output parameters in DynamoDB; 2. write large solid model data as binary blob in S3, and save ARN as reference in an output parametes.

# Amazon linux 2 VM on WSL
As lambda functions are running on Amazon Linux 2 VMs, we need create the same VM on local Windows machine so that we can do some local testing.
 ## Download Amazon Linux 2 WSL installer from https://github.com/yosukes-dev/AmazonWSL
 ## Unzip the zip file to a temp folder
 ## Install and setup Amazon Linux 2 WSL
 ```bash
wsl -l -v
wsl -s Amazon2
wsl --set-version Amazon2 2
wsl
yum update -y && yum update -y
amazon-linux-extras install -y kernel-ng
yum install -y sudo awscli openssh git zsh util-linux-user passwd tar gcc g++ make
useradd -m zhn
passwd zhnvisudo
```

Add user "zhn" in the sudo list
```bash
#add "zhn     ALL=(ALL)       NOPASSWD: ALL"  in the sudoers file using vi command
vi /etc/sudoers
```

Set up zsh for easier git handling (optional)
```bash
chsh zhn -s /bin/zsh
su - zhn
curl -L https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh | sh

# add "tonotdo" as the theme for easier git usage in the .zshrc file using vi command
vi .zshrc

#run zsh now
/bin/zsh
```

Install cmake3 for project build
```bash
yum install cmake3
yum install gcc-c++ libcurl-devel
export CC=gcc
export CXX=g++
yum install zlib-devel zlib-static openssl-devel openssl-static

```

# lambda-prism local-build
This repo build a C++ Lambda function on a local workstation and then deploys it with the CLI.   
A YouTube walk through of this repo can also be found [here](https://youtu.be/LaDrQqrrmrI).

 ## Install Some Dependencies
 ```bash
sudo yum install cmake3
sudo yum install make
sudo yum install zip
sudo yum install build-essential gdb

#make cmake3 as the default cmake (instead of the old cmake)
sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake 10 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake \
--family cmake

sudo alternatives --install /usr/local/bin/cmake cmake /usr/bin/cmake3 20 \
--slave /usr/local/bin/ctest ctest /usr/bin/ctest3 \
--slave /usr/local/bin/cpack cpack /usr/bin/cpack3 \
--slave /usr/local/bin/ccmake ccmake /usr/bin/ccmake3 \
--family cmake

```

## Build the AWS C++ SDK
These steps install the C++ SDK into the `~/install` directory and clones all the directories into `~`. This can obviously be altered if desired.    
We are also only installing the `core` package. Other packages may be required for more involved Lambda functions. 
```bash
mkdir ~/install
cd ~
git clone https://github.com/aws/aws-sdk-cpp.git
cd aws-sdk-cpp
mkdir build
cd build
cmake3 .. -DBUILD_ONLY="core" \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -DENABLE_UNITY_BUILD=ON \
  -DCUSTOM_MEMORY_MANAGEMENT=OFF \
  -DCMAKE_INSTALL_PREFIX=~/install \
  -DENABLE_UNITY_BUILD=ON
make
make install
```

## Build the AWS C++ Lambda Runtime
```bash
cd ~
git clone https://github.com/awslabs/aws-lambda-cpp-runtime.git
cd aws-lambda-cpp-runtime
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_INSTALL_PREFIX=~/install
make
make install
```

## Build the Actual C++ Lambda Function
```bash
cd ~
ssh-keygen -t rsa -b 4096
cat ~/.ssh/id_rsa.pub
#add public access key to github repos
git config --global user.email "huili_han@yahoo.com"
git config --global user.name "everetthan"
mkdir ~/git
cd ~/git
git clone git@github.com:everetthan/lambda-prism.git
cd ~/git/lambda-prism
mkdir build
cd build
cmake3 .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/install
make
make aws-lambda-package-demo
```

## Make IAM Role for the Lambda Function
We need to create and IAM role that the can be attached to the lambda function when it is deployed. Note the rights in this role may need to be expanded for more complex Lambda functions.  
First create a JSON file that defines the required permissions as shown below.
```JSON
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": {"Service": ["lambda.amazonaws.com"]},
      "Action": "sts:AssumeRole"
    }
  ]
}
```
Then create the IAM role in the CLI as shown below.
```bash
aws iam create-role --role-name lambda-prism2 --assume-role-policy-document file://trust-policy.json
```
The output of the above command will include the ARN of the new role. You must copy this ARN. It will be required when you deploy the Lambda function. It will most like have the form `arn:aws:iam::<your AWS account number>:role/lambda-prism`. 
result arn: 
```bash
arn:aws:iam::788766113629:role/lambda-prism2
```

Next attached the `AWSLambdaVPCAccessExecutionRole` or `AWSLambdaBasicExecutionRole` policy to the new role to allow the Lambda function. This is performed with the following awscli command.

```bash 
aws iam attach-role-policy --role-name lambda-prism2 --policy-arn arn:aws:iam::aws:policy/service-role/AWSLambdaVPCAccessExecutionRole
```

## Deploy 
We can now deploy the lambda function with the following CLI command.

```bash
aws lambda create-function --function-name lambda-prism2 \
  --role arn:aws:iam::788766113629:role/lambda-prism2 \
  --runtime provided --timeout 15 --memory-size 1024 \
  --handler demo --zip-file fileb://demo.zip
```

After creating the lambda-prism2 function, the function code can be updated using the following awscli command:
```bash
aws lambda update-function-code \
--function-name lambda-prism2 \
--region us-east-1 \
--zip-file fileb://demo.zip
```
## Config lambda-prism2 with EFS and Environment Variables

To run the 3D modeling code, an environment variable `CATDictionaryPath` must be set so that some shared object libraries can be dynamically loaded and called. After some try-and-error, it seems that we can save the dictionary data in the temp data storage assoicated with Lambda function with a fixed path, and Config the following environment variable in the lambda-prism2 console: `CATDictionaryPath=/mnt/dictionary`

### AWS EFS 
An AWS EFS is configed with the following keep options:
1. To reduce cost, the EFS is only linked to a single zone us-east-1f;
2. An EFS endpoint is created with a subfolder so that this efs can be used for other lambda functions (using different subfolders). The configuration options of the endpoint are:
Name – dictionary files
User ID – 1001
Group ID – 1001
Path – /dictionary
Permissions – 755
Owner user ID – 1001
Group user ID – 1001

### AWS EC2
To upload the dictionary data from local disk to AWS EFS, we need to create an AWS EC2 instance with SSH and mount the EFS on it. It should be pointed out that:
1. The subnet of networking must be set to us-east-1f too.
2. the ssh command is `ssh -i "ec2 for dictionary upload.pem" ec2-user@ec2-34-239-175-224.compute-1.amazonaws.com
3. The access mode of mounted folder is changed with
```bash
cd /mnt/efs
sudo chmod 755 fs1
```
4. Use winSCP to copy dictionary files from local disk to EC2

### Config the VPC in the lambda-prism2 console. 
I used only us-east-1f subnet to reduce cost.

### Config the file system in the lambda-prism2 console
Select EFS to mount.

## Test
```bash
aws lambda invoke --function-name lambda-prism2 --cli-binary-format raw-in-base64-out --payload '{"primitive_type": "primitive_pyramid", "location_X": 0, "location_Y": 0, "location_Z": 0, "size_length": 100, "size_width": 100, "size_height": 40}' output.json
```

## References
- [Introducing the C Lambda Runtime](https://aws.amazon.com/blogs/compute/introducing-the-c-lambda-runtime/)
- [C++ Sample Lab](https://github.com/awslabs/aws-lambda-cpp)
- [AWS CLI - Invoke Lambda](https://docs.aws.amazon.com/cli/latest/reference/lambda/invoke.html#examples)
- [AWS CLI - Payload Error](https://stackoverflow.com/questions/60310607/amazon-aws-cli-not-allowing-valid-json-in-payload-parameter)
- [YouTube Walk Through](https://youtu.be/LaDrQqrrmrI)
