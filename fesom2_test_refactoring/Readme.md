## All you need to run FESOM2 for 1 day on pi mesh

This is basis for FESOM2 sanity checks. Includes:

- pi mesh with several partitionings
- forcing for one day
- initial conditions
- mkrun (to easily create FESOM2 experiments)
- fcheck (to check the result against reference)

To use it you have to have Docker installed. 

### Get the image
Better to download the lates working image:

```
docker pull koldunovn/fesom2_test:refactoring
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
docker run -it -v "$(pwd)"/fesom2:/fesom/fesom2 fesom2_test:refactoring /bin/bash
```

This should get you inside the container. You now can edit the files in your fesom2 folder (on MacOS or Linux), but run things inside the container.

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

### Checkout and run the model within container

```bash
# run container with an image
docker run -it fesom2_test:fesom2.1 /bin/bash
# Clone repository, while inside the container
git clone https://github.com/FESOM/fesom2.git
cd fesom2
# Compile model
bash -l configure.sh ubuntu
# Create test run
mkrun pi test_pi -m docker
# change to the folder with test run
cd work_pi
# run the model
./job_docker_new
# check the result
fcheck .
```
