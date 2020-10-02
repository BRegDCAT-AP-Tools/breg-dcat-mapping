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

The tool is based on [Drupal](https://www.drupal.com). This projects contains an installation guide and an initial database dump (`dcat-mapping-database.sql`). Follow Drupal's [documentation](http://drupal.org/documentation) to configure a Drupal project.

The requirements and service dependencies for the local environment are:

* PHP 5.6.
* Drupal 7.42.
* Virtuoso triple store.