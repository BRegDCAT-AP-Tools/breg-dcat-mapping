# BREG-DCAT Mapping Tool

The BRegDCAT-AP v2 _Mapping Tool_ will allow European public administrations to create mappings in order to harmonise different data models used for describing base registries, either within a country or across borders, to another data model, being the BRegDCAT-AP v2 or any other data model. 

This tool can also visualise the mappings, export them in a machine-readable format, and analyse the coverage between the two mapped data models.

## Deployment

### Docker

A self-contained [docker-compose](https://docs.docker.com/compose/install/) configuration file is provided to ease the deployment process:

    $ cd path_to_mapping
    $ docker-compose up --build

The application can be then accessed on http://localhost:40081/

### Local deployment 

The tool is based on [Drupal](https://www.drupal.com). Follow Drupal's [documentation](http://drupal.org/documentation) to configure a Drupal project.


The requirements and service dependencies for the local environment are:

To deploy the Public Service Description Editor locally, the administration will require PHP and Drupal environments installed on their webserver. The PHP version used is 5.6.15; the Drupal version is 7.42. Finally, a Virtuoso Triple store is needed to store the data created by the users.


* PHP 5.6.
* Drupal 7.42.
* Virtuoso triple store.


This projects contains an installation guide and an initial database dump (`dcat-mapping-database.sql`) only valid for Drupal deployment. In this database has some configurations thahth must be modified to work in other enviroments:

* ARC2 store settings -> admin/config/services/arc2_store at Drupal configuration
* SPARQL Endpoints Registry -> admin/structure/sparql_registry at Drupal configuration

## Virtuoso

Virtuoso endpoints is hardcoded in CPSVAPmapping and editmapping modules in /sites/all/modules/ folder. Review this URL and adapt to your instalation.
