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
docker pull koldunovn/fesom2_test:fesom2.1
```

Or you can buld it by yourself:

```
docker build --tag=fesom2_test .
    
```
### Checkout and run the model

```bash
# run container with an image
docker run -it fesom2_test /bin/bash
# Clone repository
https://github.com/FESOM/fesom2.git
cd fesom2
# Compile model
bash -l configure.sh ubuntu
# Create test run
mkrun pi test_pi -m docker
# change to the folder with test run
cd work_pi
# make job file executable
chmod +x job_docker_new
# run the model
./job_docker_new
# check the result
fcheck .
```
