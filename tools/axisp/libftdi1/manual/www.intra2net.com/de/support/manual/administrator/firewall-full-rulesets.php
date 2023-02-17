<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Vollst&auml;ndige Regellisten | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="firewall.php" title="Teil&nbsp;5.&nbsp;Firewall"><link rel="prev" href="firewall-profiles-provider.php" title="34.3. Providerprofile"><link rel="next" href="firewall-full-rulesets-rulesets.php" title="35.2. Regellisten">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="firewall-full-rulesets.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="firewall-full-rulesets.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">35. Kapitel - Vollst&auml;ndige Regellisten</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="firewall-profiles-provider.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;5.&nbsp;Firewall</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="firewall-full-rulesets-rulesets.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="firewall-full-rulesets"></a>35. Kapitel - Vollst&auml;ndige Regellisten</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="firewall-full-rulesets.php#firewall-full-rulesets-components">35.1. Komponenten</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-full-rulesets.php#firewall-full-rulesets-components-services">35.1.1. Dienste</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets.php#firewall-full-rulesets-components-netgroups">35.1.2. Netzgruppen</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets.php#firewall-full-rulesets-components-magics">35.1.3. Automatische Objekte</a></span></dt></dl></dd><dt><span class="sect1"><a href="firewall-full-rulesets-rulesets.php">35.2. Regellisten</a></span></dt><dd><dl><dt><span class="sect2"><a href="firewall-full-rulesets-rulesets.php#firewall-full-rulesets-rulesets-basics">35.2.1. Grundeinstellungen</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets-rulesets.php#firewall-full-rulesets-rulesets-traversal">35.2.2. Durchlaufen der Regelliste</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets-rulesets.php#firewall-full-rulesets-rulesets-combination">35.2.3. Verkn&uuml;pfung der Regel-Kriterien</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets-rulesets.php#firewall-full-rulesets-rulesets-actions">35.2.4. Die Aktionen</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets-rulesets.php#firewall-full-rulesets-rulesets-extra">35.2.5. Extra-Optionen</a></span></dt><dt><span class="sect2"><a href="firewall-full-rulesets-rulesets.php#firewall-full-rulesets-rulesets-provider">35.2.6. Besonderheiten bei Provider-Regellisten</a></span></dt></dl></dd></dl></div><a class="indexterm" name="firewall-full-rulesets1"></a><p>Vollst&auml;ndige Firewall-Regellisten erlauben die volle Funktionalit&auml;t der Firewall einzusetzen
  und sind daher etwas komplexer zu konfigurieren als die Firewall-Profile.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="firewall-full-rulesets-components"></a>35.1. Komponenten</h2></div></div></div><p>Um die Firewall-Konfigurationsoberfl&auml;che nicht mit IP-Adressen und Portnummern zu
      &uuml;berfrachten, werden IPs, Netze etc. in Netzgruppen sowie Protokolle, Portnummern und
      -bereiche in Diensten zusammengefasst. Diese werden vorher zentral zusammengestellt und k&ouml;nnen
      dann in allen Firewall-Regeln eingesetzt werden. Zus&auml;tzlich werden die wichtigsten Dienste
      bereits in der Grundkonfiguration vordefiniert mit ausgeliefert.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-components-services"></a>35.1.1. Dienste</h3></div></div></div><a class="indexterm" name="firewall-full-rulesets-components-services1"></a><a class="indexterm" name="firewall-full-rulesets-components-services2"></a><p>Unter &#8222;Netzwerk &gt; Firewall &gt; Dienste&#8220; k&ouml;nnen Protokolle und Portnummern
        unter einem Dienst-Namen zusammengefasst werden. Dadurch werden sie in Firewall-Regeln
        nutzbar.</p><p>Ein Dienst besteht aus frei eingetragenen Ports und Protokollen (<span class="guimenuitem">Freier
          Dienst</span>) sowie aus anderen, bereits konfigurierten Diensten
          (<span class="guimenuitem">Verwendete Dienste</span>). Dadurch k&ouml;nnen Dienste aus mehreren
        anderen Diensten zusammengesetzt werden. Dies macht vor allem dann Sinn, wenn ein Protokoll
        aus mehreren Unterprotokollen besteht. Ein gutes Beispiel hierf&uuml;r ist FTP, welches sich aus
        der FTP-Kontrollverbindung und der FTP-Datenverbindung zusammensetzt.</p><p>Bei den Protokollen TCP und UDP k&ouml;nnen sowohl Quell- als auch Zielports angegeben
        werden. Beide Male sind Sie nicht auf einzelne Ports beschr&auml;nkt, sondern k&ouml;nnen auch
        komplette Portbereiche (wie z.B. Zielports 5000 bis 5050 f&uuml;r die Fernwartung des
        Intranator-Herstellers) konfigurieren.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Beachten Sie bitte, dass bei TCP typischerweise nur die Zielports festgelegt sind und
          der Quellport vom Client frei gew&auml;hlt werden kann. Daher wird normalerweise nur der
          Zielport im Intranator eingetragen.</p></td></tr></table></div><a class="indexterm" name="d0e11149"></a><a class="indexterm" name="d0e11150"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-components-netgroups"></a>35.1.2. Netzgruppen</h3></div></div></div><a class="indexterm" name="firewall-full-rulesets-components-netgroups1"></a><a class="indexterm" name="firewall-full-rulesets-components-netgroups2"></a><p>Unter &#8222;Netzwerk &gt; Firewall &gt; Netzgruppen&#8220; k&ouml;nnen IPs, IP-Netze und
        IP-Bereiche als Netzgruppe zusammengefasst werden. Dadurch sind sie in Firewall-Regeln
        nutzbar. Alle Rechner, Netzbereiche, Routings etc., die Sie im Intranator in den
        entsprechenden Men&uuml;s eingetragen haben, sind direkt als Netzobjekte in der Firewall
        verf&uuml;gbar und m&uuml;ssen nicht zuerst als Netzgruppe konfiguriert werden.</p><p>Genau wie bei den Diensten kann eine Netzgruppe andere Netzgruppen enthalten.</p><p>Einzelne IPs werden unter <span class="guimenuitem">Freier Rechner/Subnetz</span> mit der
        Netzmaske 255.255.255.255 eingetragen. M&ouml;chten Sie einen Netzbereich konfigurieren, der auch
        als IP-Netz darstellbar ist (z.B. IPs von 192.168.1.0 bis 192.168.1.255), dann empfiehlt es
        sich, diesen als IP-Netz mit der passenden Netzmaske (im Beispiel IP 192.168.1.0 mit
        Netzmaske 255.255.255.0) einzutragen. Dies f&uuml;hrt intern zu schlankeren und schnelleren
        Firewallregeln.</p><a class="indexterm" name="d0e11173"></a><a class="indexterm" name="d0e11174"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-components-magics"></a>35.1.3. Automatische Objekte</h3></div></div></div><p>Der Intranator fasst ihm bekannte Objekte zu automatischen Objekten zusammen. Einige
        dieser Objekte h&auml;ngen auch vom aktuellen Zustand ab, z.B. der aktuellen Internet-IP. Diese
        k&ouml;nnen direkt in Firewall-Regeln eingesetzt werden und bed&uuml;rfen keiner weiteren
        Konfiguration.</p><p>Liste der automatischen Objekte:</p><div class="informaltable"><table border="1"><colgroup><col><col></colgroup><thead><tr><th>Objekt</th><th>Beschreibung</th></tr></thead><tbody><tr><td>Rechner und Bereiche</td><td>Alle im Intranator definierten Rechner und Bereiche. Bei DHCP-Bereichen
                betrifft dies nur die belegten IPs.</td></tr><tr><td>DHCP-Bereiche</td><td>Alle DHCP-Bereiche (auch die nicht belegten IPs).</td></tr><tr><td>Fernzugriff-Anschl&uuml;sse</td><td>IP-Adressen, die f&uuml;r Fernzugriff konfiguriert sind.</td></tr><tr><td>Entfernte VPN Netze</td><td>Die Netze hinter den aktuell aktiven VPN-Gegenstellen. Bei &#8222;LAN zu
                Host&#8220;-Verbindungen ist dies die VPN-Gegenstelle selbst.</td></tr><tr><td>Intranator LAN IPs</td><td>IP-Adressen des Intranators in allen seinen Netzen vom Typ &#8222;LAN mit NAT&#8220; und
                &#8222;LAN ohne NAT&#8220;.</td></tr><tr><td>Alle lokalen Netze</td><td>Alle Netze (&#8222;LAN mit NAT&#8220; und &#8222;LAN ohne NAT&#8220;) und Routings.</td></tr><tr><td>Broadcast-IPs aller lokalen Netze</td><td>Broadcast-IPs aller lokalen Netze.</td></tr><tr><td>Aktuelle Internet IP</td><td>Aktuelle IP des Intranators im Internet. Ist das System offline, so trifft
                diese Bedingung nicht mehr zu.</td></tr><tr><td>Internet</td><td>Alles au&szlig;erhalb der lokalen Netze und VPNs.</td></tr></tbody></table></div></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="firewall-profiles-provider.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="firewall.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="firewall-full-rulesets-rulesets.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">34.3. Providerprofile&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;35.2. Regellisten</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>