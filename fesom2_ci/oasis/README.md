This is the branch of the OASIS3-MCT climate coupler currently recommended for users. It corresponds to the official OASIS3-MCT_5.0 released in December 2022 + important bugfixes since then.

Developments for the future OASIS3-MCT_6.0 will be done in other branches and then merged to the master branch.

For changes between the different versions of OASIS3-MCT, please refer to Appendix B of the User Guide (in oasis3-mct/doc/oasis3mct_UserGuide.pdf).

Please keep us informed of your progress with OASIS3-MCT and do not forget to cite the following latest reference in your paper describing your coupled model results.::
A. Craig, S. Valcke, L. Coquart, 2017: Development and performance of a new version of the OASIS coupler, OASIS3-MCT_3.0, Geosci. Model Dev., 10, 3297-3308,https://doi.org/10.5194/gmd-10-3297-2017, 2017.   

If you have problems or questions, please check the forum on the OASIS3-MCT web site (https://www.cerfacs.fr/site-oasis/forum/oa_main.php) or contact us at oasishelp@cerfacs.fr .

Bugfixes since OASIS3-MCT_5.0 official release:

- 31/10/2022: Add support for multiple grids per partition
- 01/06/2022: Bugfix for load balacing analysis freezing when all processes are not involved in the coupling observed and solved by Eric
- 01/06/2022: Fix use of uninitialized rglo for mask in grid writing.
- 01/06/2022: Add oasis_def_var interface with 2d id_var_shape.  id_var_shape is not used anymore, but we provide an interface with a 1d and 2d argument for backwards compatibility.
