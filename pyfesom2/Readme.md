Installation of pyfesom2 and fdiag
==================================

Install latest [pyfesom2](https://github.com/FESOM/pyfesom2) an [fdiag](https://github.com/FESOM/fdiag). The main intention is to use with Singularity, that is why we use relatively old Ubuntu installation. 

Simple case scenario
--------------------

You should be able to pull the latest version of singularity image with `pyfesom2` and `fdiag` installed by

```
singularity pull library://koldunovn/default/pyfesom2:latest
```

And run commands as:

```bash
singularity exec pyfesom2_16.04.sif pfinterp
singularity exec pyfesom2_16.04.sif fdiag
singularity exec pyfesom2_16.04.sif pfplot
```

If you want to build it wourself
================================

Build Docker image
------------------

```bash
docker build --no-cache --tag=pyfesom2 .
```

This will create an image. To push it to Docker Hub (if you need to to it):

```bash
docker tag xxxxxxxx koldunovn/pyfesom2:16.04
docker push koldunovn/pyfesom2:16.04
```

Steps to build Singularity image:
---------------------------------
You can't build container on HPC machine, since you have to have root piveleges to do it. So you need acess to Linux box. For Mac user this means you have to install vagrant. I use [this instruction](https://www.taniarascia.com/what-are-vagrant-and-virtualbox-and-how-do-i-use-them/) to install vagrant on Mac and then [this instruction](https://sylabs.io/guides/3.0/user-guide/installation.html#singularity-vagrant-box) to get the vagrant box with singularity installation. Note, that I select version of singularity 3.5, since this is the lowest version on HCP machines I plan to use it for. In short instructions are:

```bash  
vagrant box add sylabs/singularity-3.5-ubuntu-bionic64
vagrant init sylabs/singularity-3.5-ubuntu-bionic64
mkdir data
```
You have to edit `Vagrantfile` to bind local and VM directories (makes it easy to move files around). Uncomment and edit this line:
```python
config.vm.synced_folder "./data", "/vagrant_data"
```
Alternativelly you can transpher image directly to HPC.

Get to the VM:
```bash
vagrant up
vagrant ssh
```

And build container:

```bash
singularity build /vagrant_data/pyfesom2_16.04.sif docker://koldunovn/pyfesom2:16.04
```

You will get `pyfesom2_16.04.sif` image, that can be just transphered to HPC machine. 

Using the image
---------------

Load `singularity` module on HPC. You should be able now to invoke several fesom related programs using container:

```bash
singularity exec pyfesom2_16.04.sif pfinterp
singularity exec pyfesom2_16.04.sif fdiag
singularity exec pyfesom2_16.04.sif pfplot
```

you can also run jupyter notebooks with latest pyfesom2 installed:

```
singularity exec pyfesom2_16.04.sif jupyter notebook
```
