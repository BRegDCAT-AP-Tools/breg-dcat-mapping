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

The tool is based on [Drupal](https://www.drupal.com), please see Drupal's [documentation](http://drupal.org/documentation) for more information.

The requirements and service dependencies for the local environment are:

* PHP 5.6.
* Drupal 7.42.
* Virtuoso triple store.
* MySQL.

The configuration of the **MySQL database** can be modified in `sites/default/settings.php`. It points to the `mysql` hostname of the container defined in the Compose file by default:

```
...

$databases = array (
  'default' => 
  array (
    'default' => 
    array (
      'database' => 'dcat-mapping',
      'username' => 'root',
      'password' => 'root',
      'host' => 'mysql',
      'port' => '',
      'driver' => 'mysql',
      'prefix' => '',
    ),
  ),
);

...
```

Modifying the configuration of the **Virtuoso triple store** would require replacing all hardcoded references to the `virtuoso` hostname in:

* `sites/all/modules/CPSVAPmapping/CPSVAPmapping.module`
* `sites/all/modules/editmapping/editmapping.module`
* `sites/all/modules/mapping/mapping.module`

Once the Drupal application is up and running please make sure to also update the SPARQL endpoint in the following configuration pages:

* *ARC2 store settings*: `admin/config/services/arc2_store`
* *SPARQL Endpoints Registry*: `admin/structure/sparql_registry`
