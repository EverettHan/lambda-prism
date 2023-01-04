<?xml version="1.0" encoding="UTF-8"?>
<!-- WARNING: YWE 15:07:06 SINGLE-CODE 2013x => NO LOCAL CHANGE EXPECTED - USE IMPORT -->
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
<xsl:output method="html" indent="yes" encoding="UTF-8"/>

  <xsl:variable name="InputProviderTitle">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='DataSourceInputProvider']/@nls"/>
  </xsl:variable>
  <xsl:variable name="OutputProviderTitle">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='DataSourceOutputProvider']/@nls"/>
  </xsl:variable>
  <xsl:variable name="DataSourceTitle">
    <xsl:value-of select="Execution/Set[@Name='Resource']/Metric[@Name='DataSource']/@nls"/>
  </xsl:variable>

  <xsl:template name="InfraDataSource">

    <xsl:if test="count(./DataSource)!=0">

    <tr>
      <td>
        <table class="frame" width="100%"><!-- LEVEL1: TABLE DATASOURCE WITH IN/OUT PROVIDERS-->
          <tr>
            <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                                onmouseout="this.className='titleMode clickable';"
                                onclick="toggle_visibility_by_id('DataSource','plusminusDataSource')">

              <xsl:value-of select="$DataSourceTitle"/>&#160;<img src="Data\Plus.gif" class="clickable" id="plusminusDataSource"><xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute></img>

            </th>
          </tr>

          <tr>
            <td>
              <span id="DataSource" class="displayHide">
                <!-- 3.1- Display list of Data source -->
                <dd>
                  <table border="0" WIDTH="95%">
                    <!-- Display DataSource IN -->
                    <xsl:for-each select="./DataSource[@type='In']">
                      <!-- DATASOURCE SECTION ============================================ DEB -->
                      <!-- DATASOURCE SECTION ============================================ DEB -->
                      <!-- DATASOURCE SECTION ============================================ DEB -->
                      <tr>
                        <td colspan="2">
                          <table class="frame" width="100%">
                            <xsl:choose>
                              <xsl:when test="count(Set[@Name='Credential']/Option)=0">
                                <tr>
                                  <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                     <xsl:value-of select="$InputProviderTitle"/>&#160;: <xsl:value-of select="@Name"/>  
                                  </th>
                                </tr>
                              </xsl:when>

                              <xsl:otherwise>
                                <tr>
                                  <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';"
                                                        onmouseout="this.className='titleMode clickable';">
                                    <xsl:attribute name="onclick">toggle_visibility_by_id('DataSourceIn','plusminusDataSourceIn')</xsl:attribute>
                                      <xsl:value-of select="$InputProviderTitle"/>&#160;: <xsl:value-of select="@Name"/> &#160;  
                                    <img src="Data\Plus.gif" class="clickable">
                                      <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                                      <xsl:attribute name="id">plusminusDataSourceIn</xsl:attribute>
                                    </img>
                                  </th>
                                </tr>
                                <tr>
                                  <td >
                                    <span id="DataSourceIn" class="displayHide">
                                      <xsl:call-template name="DataSource"/>
                                    </span>
                                  </td>
                                </tr>
                              </xsl:otherwise>
                            </xsl:choose>
                          </table>
                        </td>
                      </tr>


                      <!-- DATASOURCE SECTION ============================================ END -->
                      <!-- DATASOURCE SECTION ============================================ END -->
                      <!-- DATASOURCE SECTION ============================================ END -->
                    </xsl:for-each>

                    <!-- Display DataSource OUT -->
                    <xsl:for-each select="./DataSource[@type='Out']">
                      <!-- DATASOURCE SECTION ============================================ DEB -->
                      <!-- DATASOURCE SECTION ============================================ DEB -->
                      <!-- DATASOURCE SECTION ============================================ DEB -->
                      <tr>
                        <td>
                          <table class="frame" width="100%">
                            <xsl:choose>
                              <xsl:when test="count(Set[@Name='Credential']/Option)=0">
                                <tr>
                                  <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                    <xsl:value-of select="$OutputProviderTitle"/>&#160;: <xsl:value-of select="@Name"/>
                                  </th>
                                </tr>
                              </xsl:when>

                              <xsl:otherwise>
                                <tr>
                                  <th class="titleMode" onmouseover="this.className='highlightTitleMode clickable';" onmouseout="this.className='titleMode clickable';">
                                    <xsl:attribute name="onclick">toggle_visibility_by_id('DataSourceOut','plusminusDataSourceOut')</xsl:attribute>
                                    <xsl:value-of select="$OutputProviderTitle"/>&#160;: <xsl:value-of select="@Name"/> &#160;  
                                    <img src="Data\Plus.gif" class="clickable">
                                      <xsl:attribute name="height"><xsl:copy-of select="$iconHSize" /></xsl:attribute>
                                      <xsl:attribute name="id">plusminusDataSourceOut</xsl:attribute>
                                    </img>
                                  </th>
                                </tr>
                                <tr>
                                  <td >
                                    <span id="DataSourceOut" class="displayHide">
                                      <xsl:call-template name="DataSource"/>
                                    </span>
                                  </td>
                                </tr>
                              </xsl:otherwise>
                            </xsl:choose>
                          </table>
                        </td>
                      </tr>
                      <!-- DATASOURCE SECTION ============================================ END -->
                      <!-- DATASOURCE SECTION ============================================ END -->
                      <!-- DATASOURCE SECTION ============================================ END -->
                    </xsl:for-each>
                  </table>
                </dd>
              </span>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </xsl:if>

  </xsl:template>


  <!-- ====================================================== -->
  <!--                  TEMPLATE DEFINITION                   -->
  <!-- ====================================================== -->
  <!-- ============================================= -->
  <!--  DataSource Provider template                 -->
  <!-- ============================================= -->

  <!-- DATASOURCE TEMPLATE ============================================ DEB -->
  <!-- DATASOURCE TEMPLATE ============================================ DEB -->
  <!-- DATASOURCE TEMPLATE ============================================ DEB -->
  <xsl:template name="DataSource">
    <table border="1" cellspacing="1" cellpadding="3" align="right" class="objectFBDITable">
      <th class = "defaultMode" width="375"><xsl:copy-of select="$NameColumn" /></th>
      <th class = "defaultMode" width="575"><xsl:copy-of select="$ValueColumn" /></th>
      <xsl:for-each select="Set[@Name = 'Credential']/Option">
        <tr>
          <td class="defaultMode">
            <xsl:value-of select="@Name"/>
          </td>
          <xsl:choose>
            <xsl:when test="@isSet='T'">
              <td class="defaultMode">
                <xsl:value-of select="@value"/>
              </td>
            </xsl:when>
            <xsl:otherwise>
              <td>
                <i>No value set</i>
              </td>
            </xsl:otherwise>
          </xsl:choose>
        </tr>
      </xsl:for-each>
    </table>

    <!-- DATASOURCE TEMPLATE ============================================ END -->
    <!-- DATASOURCE TEMPLATE ============================================ END -->
    <!-- DATASOURCE TEMPLATE ============================================ END -->

  </xsl:template>
  <!-- End of 'DataSource' template -->


</xsl:stylesheet>
