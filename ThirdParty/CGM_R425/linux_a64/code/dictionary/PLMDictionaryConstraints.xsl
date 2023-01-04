<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Edited by XMLSpy® -->
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
  <body>
	<a href="http://plminf2e/plminf_plmdico_wiki/plm_dictionary_home_page.html"><img src="http://plminf2e/plminf_plmdico_wiki/PLMDictionaryBanner.png" border="0"/></a>
    <h2>Dictionary Constraints...</h2>
    <table border="0" cellspacing="10">
      <tr bgcolor="#fff5d7">
        <th>errorNo</th>
		<th>error Message</th>
		<th>Apply on...</th>
      </tr>
	  <xsl:for-each select="AllConstraints/ConstraintSet/Constraint">
		  <xsl:sort select="attribute::errorNo"/>
		  <xsl:variable name="errorCode" select="attribute::errorNo"/>
		  <tr>
			<td valign="top"><a name="{$errorCode}"/><b><xsl:value-of select="attribute::errorNo"/></b></td>
			<td><xsl:copy-of select="errorMsg"/></td>
			<td><xsl:value-of select="parent::node()/attribute::applyOn"/></td>
		</tr>
	 </xsl:for-each>
	 <xsl:for-each select="AllMlcConstraints/mlcConstraint">
		  <xsl:sort select="attribute::errorNo"/>
		  <tr>
			<td valign="top"><b><xsl:value-of select="attribute::errorNo"/></b></td>
			<td><xsl:copy-of select="errorMsg"/>
				<xsl:variable name="errorCode" select="attribute::errorNo"/>
				<xsl:if test="not($errorCode = 'D500')">
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]">
						<li><xsl:value-of select="attribute::declarationPath"/>
						</li>
					</xsl:for-each>
					</ul>
				</xsl:if>
				<xsl:if test="$errorCode = 'D500'">
					<ul>
					<li>The following attributes can change their values without any restrictions :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/anyNewValue">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
						</li>
					</xsl:for-each>
					</ul>
					<li>The following old/new value pairs are allowed :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/valuePair">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
							<ul>
								<li>old value = <xsl:value-of select="attribute::oldValue"/></li>
								<li>new value = <xsl:value-of select="attribute::newValue"/></li>
							</ul>
						</li>
					</xsl:for-each>
					</ul>
					<li>When the value is a space separated list of strings, then the following attributes can add new strings to the list :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/valueAddition">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
						</li>
					</xsl:for-each>
					</ul>
					<li>When the value is a space separated list of strings, then the following attributes can remove a string from the list :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/valueDeletion">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
						</li>
					</xsl:for-each>
					</ul>
					<li>When the value is an integer, the following parameters can increase their value :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/valueIncrease">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
						</li>
					</xsl:for-each>
					</ul>
					<li>When the value for the parameter is undefined, the following parameters can define a new value :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/newDefinedValue">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
						</li>
					</xsl:for-each>
					</ul>
					<li>When the value for the parameter is defined, the following parameters can be removed :</li>
					<ul>
					<xsl:for-each select="allow[not(@isException='Yes')]/newUndefinedValue">
						<li><xsl:value-of select="parent::allow/attribute::parameterPath"/>
						</li>
					</xsl:for-each>
					</ul>
					</ul>
				</xsl:if>
			</td>
		</tr>
	 </xsl:for-each>

    </table>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>
