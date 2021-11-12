## All you need to run FESOM2 for 1 day on pi mesh

This is basis for FESOM2 sanity checks. Includes:

- pi mesh with several partitionings
- forcing for one day
- initial conditions
- mkrun (to easily create FESOM2 experiments)
- fcheck (to check the result against reference)

To use it you have to have Docker installed. 

### TLDR; testing FESOM2 with docker container
Install Docker ([Linix](https://docs.docker.com/engine/install/ubuntu/), [MacOs](https://docs.docker.com/desktop/mac/install/), [Windows](https://docs.docker.com/desktop/windows/install/)(not sure it will work, but, hey:)))

Pull the image (you have to do it only once)
```
docker pull koldunovn/fesom2_test:refactoring2
```

Clone repository
```bash
git clone https://github.com/FESOM/fesom2.git
#checkout branch if necessary
cd fesom2
git checkout feature_branch
cd ../ #important to be outside fesom2 directory at this point
```

Run the container
```bash
docker run -it -v "$(pwd)"/fesom2:/fesom/fesom2 koldunovn/fesom2_test:refactoring2 /bin/bash
```
You will end up inside the container. Now you can test FESOM2, develop new feature and test again. The simplest test run is (when within the container):

```bash
cd fesom2
./test.sh
```

**NOTE** you can still edit the fesom2 source folder in your host OS, using 21st century tools, like VSCode, the `fesom2` folder is *mounted* inside the container. So the workflow is: (i) edit source on the disk with usual tools (ii) compile and test things in the container (iii) repeat.


## More advanced topics (some a bit repetative)
### Get the image
Better to download the lates working image:

```
docker pull koldunovn/fesom2_test:refactoring2
```

Or you can buld it by yourself:

```
docker build --tag=fesom2_test .
    
```

### Checkout FESOM2 code (outside container) and run it within container

The most common scenario is that you would like to develop the code on your machine, using VS Code or other modern editors, and then run it in the controlled environment of the container. For this you should mount the folder with the code on your machine to folder within the container.

Checkout FESOM2 code on your machine:

```bash
git clone https://github.com/FESOM/fesom2.git
```

Stay in the same folder and run the container with volume mount option:

```bash
docker run -it -v "$(pwd)"/fesom2:/fesom/fesom2 koldunovn/fesom2_test:refactoring2 /bin/bash
```

This should get you inside the container. You now can edit the files in your fesom2 folder (on MacOS or Linux), but run things inside the container. Easy way to run the test is to execute `test.sh` script within the container. Below is besically description of the steps this test does:

When inside the container, to compile:

```bash
cd fesom2
bash -l configure.sh ubuntu
```

To prepare the run (this will do the test with pi mesh):

```bash
mkrun pi test_pi -m docker
```
More details on what is going on here is in the [mkfesom documentation](https://github.com/FESOM/mkfesom).
To run the model:

```bash
cd work_pi/
./job_docker_new
```
To check the result:

```bash
fcheck .
```

