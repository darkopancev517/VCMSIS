<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Verbindung | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-zywall-usg.php" title="51. Kapitel - VPN mit ZyXEL ZyWALL USG"><link rel="prev" href="vpn-zywall-usg-certificates.php" title="51.3. Zertifikate"><link rel="next" href="vpn-zywall-usg-intranator.php" title="51.5. Intranator">
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

<a href="vpn-zywall-usg-connection.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-zywall-usg-connection.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">51.4. Verbindung</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-zywall-usg-certificates.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">51. Kapitel - VPN mit ZyXEL ZyWALL USG</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-zywall-usg-intranator.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-zywall-usg-connection"></a>51.4. Verbindung</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="vpn-zywall-usg-connection-ike"></a>51.4.1. IKE / Phase 1</h3></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml;
              <span class="guimenu">Configuration&nbsp;&gt;&nbsp;VPN&nbsp;&gt;&nbsp;IPSec
              VPN, Reiter VPN Gateway</span>. Legen Sie mit <span class="guibutton">Add</span> eine neue
            IKE-Verbindung zu einer Gegenstelle an.</p></li><li><p>Klicken Sie auf <span class="guibutton">Show Advanced Settings</span>, um alle n&ouml;tigen Felder
            angezeigt zu bekommen.</p></li><li><p>Geben Sie die IP oder den DNS-Namen des Intranators als Peer Gateway Address ein.
            Auch wenn der Intranator eine dynamische IP mit DynDNS verwendet, m&uuml;ssen Sie
              <span class="guimenuitem">Static Address</span> w&auml;hlen. </p></li><li><p>Stellen Sie die Authentifizierung auf Zertifikate und w&auml;hlen das vorhin erstellte
            Zertifikat f&uuml;r die ZyWALL aus.</p></li><li><p>W&auml;hlen Sie AES128 und SHA1 als Proposal aus, die passende <span class="guimenuitem">Key
              Group</span> ist DH2.</p></li><li><p> Sollte sich die Zywall oder der Intranator hinter einem NAT-Router befinden, m&uuml;ssen
            Sie die Option <span class="guimenuitem">NAT Traversal</span> aktivieren. </p></li></ol></div><div class="mediaobject"><img src="../images/vpn/zywall-usg/zywall-vpn-ike1.png"></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="vpn-zywall-usg-connection-ipsec"></a>51.4.2. IPSec / Phase 2</h3></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml;
              <span class="guimenu">Configuration&nbsp;&gt;&nbsp;VPN&nbsp;&gt;&nbsp;IPSec
              VPN, Reiter VPN Connection</span>. Legen Sie mit <span class="guibutton">Add</span> eine
            neue IPSec-Verbindung an.</p></li><li><p>Legen Sie ein Netzwerkobjekt f&uuml;r das Netz der Gegenstelle an. Verwenden Sie dazu das
            Men&uuml; <span class="guimenu">Create new Object&nbsp;&gt;&nbsp;Address</span>. Verwenden
            Sie als Typ <code class="option">SUBNET</code> und tragen die Netzadresse und Netzmaske ein.</p><div class="mediaobject"><img src="../images/vpn/zywall-usg/zywall-vpn-ipsec1.png"></div></li><li><p>Klicken Sie auf <span class="guibutton">Show Advanced Settings</span>, um alle n&ouml;tigen Felder
            angezeigt zu bekommen.</p></li><li><p>Stellen Sie die Verbindung auf Nailed Up, damit die ZyWALL die Verbindung von sich
            aus offen h&auml;lt.</p></li><li><p>W&auml;hlen Sie Site-to-site und w&auml;hlen als Gateway die eben angelegte IKE-Verbindung zum
            Intranator.</p></li><li><p> W&auml;hlen Sie als <span class="guimenuitem">Local policy</span> das zu verbindende Netz
            hinter der Zywall. W&auml;hlen Sie als <span class="guimenuitem">Remote Policy</span> das eben
            angelegte Netzwerkobjekt mit dem Netz des Intranators. </p></li><li><p>Aktivieren Sie <span class="guimenuitem">Policy Enforcement</span>, um die Sicherheit der
            Verbindung gegen Netzmanipulationen zu gew&auml;hrleisten.</p><div class="mediaobject"><img src="../images/vpn/zywall-usg/zywall-vpn-ipsec2a.png"></div></li><li><p>W&auml;hlen Sie als <span class="guimenuitem">Proposal</span> AES128 und SHA1. Stellen Sie die
              <span class="guimenuitem"> Perfect Forward Secrecy (PFS)</span> auf DH2.</p><div class="mediaobject"><img src="../images/vpn/zywall-usg/zywall-vpn-ipsec2b.png"></div></li></ol></div><p>Die Verbindung ist nun fertig konfiguriert und sollte im Hintergrund bereits aufgebaut
        werden.</p><div class="mediaobject"><img src="../images/vpn/zywall-usg/zywall-vpn-ipsec3.png"></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-zywall-usg-certificates.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-zywall-usg.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-zywall-usg-intranator.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">51.3. Zertifikate&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;51.5. Intranator</td></tr></table></div>
      
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